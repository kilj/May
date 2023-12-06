// Red Beat, 2023

#include "UI/Widget/SpellPanelWidget.h"

#include "AbilitySystem/MayAbilitySystemComponent.h"
#include "AbilitySystem/MayGameplayTags.h"
#include "AbilitySystem/Abilities/MayGameplayAbility.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Utils/MayLogChannels.h"

void USpellPanelWidget::InitWidget(const FSpellPanelWidgetData Data) {
	WidgetData = Data;

	const auto ASC = Data.AbilitySystemComponent;

	//TODO: theoretically SpellPanelWidget can subscribe here to AbilitiesGivenDelegate AFTER the delegate was fired - keep this in mind and add logic to handle this if this will be needed
	ASC->AbilitiesGivenDelegate.AddUObject(this, &ThisClass::OnStartupAbilitiesGiven);
	
	OnWidgetInited();
	MAY_ULOGW(GetOwningPlayerPawn(), TEXT("Spell panel inited."));
}

void USpellPanelWidget::OnStartupAbilitiesGiven() {
	const auto AbilitiesSpecs = GetWidgetData().AbilitySystemComponent->GetActivatableAbilities();
	for (const auto Spec : AbilitiesSpecs) {
		const auto Ability = Cast<UMayGameplayAbility>(Spec.Ability.Get());
		if (Ability == nullptr) {
			MAY_ULOGE(GetOwningPlayerPawn(), TEXT("Ability %s is not UMayGameplayAbility and will be skipped..."), *Spec.Ability.Get()->GetName());
			continue;
		}
		
		MAY_ULOGW(GetOwningPlayerPawn(), TEXT("Ability: %s"), *Ability->GetName());

		FGameplayTagContainer AbilityTagContainer;
		AbilityTagContainer.AddTag(FMayGameplayTags::Get().Ability);
		
		FGameplayTagContainer AbilityTags = Ability->AbilityTags.Filter(AbilityTagContainer);
		if (AbilityTags.Num() <= 0) {
			MAY_ULOGE(GetOwningPlayerPawn(), TEXT("Ability %s hasn't any ability tag. Please add one."), *Ability->GetName());
			return;
		}

		const auto Tag = AbilityTags.GetByIndex(0);
		
		if (AbilityTags.Num() > 1)
			MAY_ULOGW(GetOwningPlayerPawn(), TEXT("Ability %s has too many [%i] ability tags. It should have only one ability tag to identify ability. We will use first tag [%s] here..."), *Ability->GetName(), AbilityTags.Num(), *Tag.ToString());
			

		MAY_ULOGW(GetOwningPlayerPawn(), TEXT("Ability tag: %s, Input tag: %s"), *Tag.ToString(), *Ability->StartupInputTag.ToString());
		auto Info = AbilityInfo->GetAbilityInfo(Tag);
		Info.InputTag = Ability->StartupInputTag;

		OnAbilityInfoChanged(Info);
	}
	
}
