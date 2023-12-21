#include "AbilitySystem/MayAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/MayAbilityTypes.h"
#include "AbilitySystem/MayGameplayTags.h"
#include "AbilitySystem/Utils/MayAbilitySystemLibrary.h"
#include "Character/EnemyCharacter.h"
#include "Character/EnnieCharacter.h"
#include "Character/Interfaces/CombatActorInterface.h"
#include "GameFramework/Character.h"
#include "Player/EnniePlayerController.h"
#include "UI/Components/DamageTextComponent.h"
#include "Utils/MayLogChannels.h"

UMayAttributeSet::UMayAttributeSet() {
	//InitHealth(50.f);
	//InitMana(10.f);
}

void UMayAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Primary attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, Vigor, COND_None, REPNOTIFY_Always);

	//Secondary attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

	//resistance attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, ResistancePhysical, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, ResistanceMagical, COND_None, REPNOTIFY_Always);

	//Vital attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, Mana, COND_None, REPNOTIFY_Always);
}

void UMayAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) {
	Super::PreAttributeChange(Attribute, NewValue);

	ClampAttributeValues(Attribute, NewValue);
}

void UMayAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const {
	Super::PreAttributeBaseChange(Attribute, NewValue);

	ClampAttributeValues(Attribute, NewValue);
}

void UMayAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) {
	Super::PostGameplayEffectExecute(Data);

	//just collecting data about GE execution for easy further usage
	FEffectProperties Properties;
	SetEffectProperties(Data, Properties);

	const auto EffectContext = static_cast<FMayGameplayEffectContext*>(Properties.EffectContextHandle.Get());

	//handle meta attribute IncomingDamage
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute()) {
		const float IncomingDamageValue = GetIncomingDamage(); //cache meta attribute value
		SetIncomingDamage(0.f); //cleaning up after ourself

		if (IncomingDamageValue > 0.f) {
			const float NewHealth = GetHealth() - IncomingDamageValue;
			SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));

			const bool bFatal = NewHealth <= 0.f;
			if (bFatal) {
				const auto CombatActorInterface = Cast<ICombatActorInterface>(Properties.TargetAvatarActor);
				CombatActorInterface->Server_Die();

				// getting experience value from target and added it to source experience
				const auto Enemy = Cast<AEnemyCharacter>(Properties.TargetCharacter);
				if (Enemy) {
					const auto EType = UMayAbilitySystemLibrary::GetEnemyTypeInfo(GetWorld(), Enemy->EnemyType);
					const int32 Experience = EType.Experience.GetValueAtLevel(static_cast<int>(Enemy->Level));

					//TODO: handle (if needed) case when character received experience from other player or some job, interaction, etc
					AMayCharacter* Source = Cast<AMayCharacter>(Properties.SourceAvatarActor);
					ILevelInterface::Execute_AddExperience(Source, Experience);
				}
				
			} else {
				const FGameplayTagContainer TagContainer(FMayGameplayTags::Get().EffectsHitReact);
				Properties.TargetASC->TryActivateAbilitiesByTag(TagContainer);
			}
		}

		//showing floating text
		if (Properties.SourceCharacter && Properties.TargetCharacter && Properties.SourceCharacter != Properties.TargetCharacter) {
			auto EnniePC = Cast<AEnniePlayerController>(Properties.SourceCharacter->GetController());
			if (EnniePC == nullptr)
				EnniePC = Cast<AEnniePlayerController>(Properties.TargetCharacter->GetController()); //we handle here two possible situations: when enemy deals damage to the hero and when hero deals damage to the enemy, so we check Source AND Target
				
			if (EnniePC) {
				FUIDamageData DamageData;
				DamageData.bIsBlockedHit = EffectContext->IsBlockHit();
				DamageData.bIsCriticalHit = EffectContext->IsCriticalHit();
				
				EnniePC->ShowReceivedDamage(IncomingDamageValue, Properties.TargetCharacter, DamageData);
			}
		}
	}

	//handle meta attribute IncomingExperience
	if (Data.EvaluatedData.Attribute == GetIncomingExperienceAttribute()) {
		const int32 IncomingExperienceValue = static_cast<int32>(GetIncomingExperience()); //cache
		SetIncomingExperience(0.f);

		if (IncomingExperienceValue > 0.f) {
			MAY_ULOGW(Properties.SourceCharacter, TEXT("%s received experience: %i"), *Properties.SourceCharacter->GetActorNameOrLabel(), IncomingExperienceValue);

			Properties.SourceCharacter->AddExperience(IncomingExperienceValue);
		}
	}
}

void UMayAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, Health, OldHealth);
}

void UMayAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, Mana, OldMana);
}

void UMayAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, Strength, OldStrength);
}

void UMayAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, Intelligence, OldIntelligence);
}

void UMayAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, Resilience, OldResilience);
}

void UMayAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, Vigor, OldVigor);
}

void UMayAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, Armor, OldArmor);
}

void UMayAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UMayAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, BlockChance, OldBlockChance);
}

void UMayAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void UMayAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UMayAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, CriticalHitResistance, OldCriticalHitResistance)
}

void UMayAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, HealthRegeneration, OldHealthRegeneration)
}

void UMayAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, ManaRegeneration, OldManaRegeneration)
}

void UMayAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, MaxHealth, OldMaxHealth);
}

void UMayAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, MaxMana, OldMaxMana);
}

void UMayAttributeSet::OnRep_ResistancePhysical(const FGameplayAttributeData& OldResistancePhysical) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, ResistancePhysical, OldResistancePhysical);
}

void UMayAttributeSet::OnRep_ResistanceMagical(const FGameplayAttributeData& OldResistanceMagical) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, ResistanceMagical, OldResistanceMagical);
}

void UMayAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Properties) {
	Properties.EffectContextHandle = Data.EffectSpec.GetContext();
	Properties.SourceASC = Properties.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Properties.SourceASC) && Properties.SourceASC->AbilityActorInfo.IsValid() && Properties.SourceASC->AbilityActorInfo->AvatarActor.IsValid()) {
		Properties.SourceAvatarActor = Properties.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Properties.SourceController = Properties.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Properties.SourceController == nullptr && Properties.SourceAvatarActor != nullptr) {
			if (const APawn* Pawn = Cast<APawn>(Properties.SourceAvatarActor)) {
				Properties.SourceController = Pawn->GetController();
			}
		}
		if (Properties.SourceController) {
			Properties.SourceCharacter = Cast<AMayCharacter>(Properties.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid()) {
		Properties.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Properties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Properties.TargetCharacter = Cast<AMayCharacter>(Properties.TargetAvatarActor);
		Properties.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Properties.TargetAvatarActor);
	}
}

void UMayAttributeSet::ClampAttributeValues(const FGameplayAttribute& Attribute, float& NewValue) const {
	//all our attributes should be greater than zero, so at first check this
	if (NewValue < 0.f)
		NewValue = 0.f;
	
	if (Attribute == GetHealthAttribute())
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	
	if (Attribute == GetManaAttribute())
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
}
