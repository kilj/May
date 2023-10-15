#include "AbilitySystem/MayAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Utils/MayLogChannels.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"

UMayAttributeSet::UMayAttributeSet() {
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(10.f);
	InitMaxMana(100.f);
}

void UMayAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
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

	FEffectProperties Properties;
	SetEffectProperties(Data, Properties);

	// this code will call AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate twice, but somehow there are some people who recommends such approach
	// if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	// 	SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	//
	// if (Data.EvaluatedData.Attribute == GetManaAttribute())
	// 	SetMana(FMath::Clamp(GetMana(), 0.0f, GetMaxMana()));
}

void UMayAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, Health, OldHealth);
}

void UMayAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, MaxHealth, OldMaxHealth);
}

void UMayAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, Mana, OldMana);
}

void UMayAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, MaxMana, OldMaxMana);
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
			Properties.SourceCharacter = Cast<ACharacter>(Properties.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid()) {
		Properties.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Properties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Properties.TargetCharacter = Cast<ACharacter>(Properties.TargetAvatarActor);
		Properties.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Properties.TargetAvatarActor);
	}
}

void UMayAttributeSet::ClampAttributeValues(const FGameplayAttribute& Attribute, float& NewValue) const {
	if (Attribute == GetHealthAttribute())
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	
	if (Attribute == GetManaAttribute())
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
}
