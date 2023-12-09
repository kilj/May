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

	ASC->AbilityGivenDelegate.AddUObject(this, &USpellPanelWidget::OnAbilityGiven);
	ASC->AbilityCommittedCallbacks.AddLambda([this](UGameplayAbility* Ability)
	{
		OnAbilityCommited(Ability);
	});

	OnWidgetInited();
}

void USpellPanelWidget::OnAbilityGiven(const FGameplayAbilitySpec& AbilitySpec) {
	const auto Ability = Cast<UMayGameplayAbility>(AbilitySpec.Ability.Get());
	if (Ability == nullptr) {
		MAY_ULOGE(GetOwningPlayerPawn(), TEXT("Ability %s is not UMayGameplayAbility and will be skipped..."), *AbilitySpec.Ability.Get()->GetName());
		return;
	}
		
	FGameplayTagContainer AbilityTagContainer;
	AbilityTagContainer.AddTag(FMayGameplayTags::Get().Ability);

	const FGameplayTagContainer AbilityTags = Ability->AbilityTags.Filter(AbilityTagContainer);
	if (AbilityTags.Num() <= 0) {
		MAY_ULOGE(GetOwningPlayerPawn(), TEXT("Ability %s hasn't any ability tag. Please add one."), *Ability->GetName());
		return;
	}

	const auto Tag = AbilityTags.GetByIndex(0);
		
	if (AbilityTags.Num() > 1)
		MAY_ULOGW(GetOwningPlayerPawn(), TEXT("Ability %s has too many [%i] ability tags. It should have only one ability tag to identify ability. We will use first tag [%s] here..."), *Ability->GetName(), AbilityTags.Num(), *Tag.ToString());
			

	MAY_ULOGW(GetOwningPlayerPawn(), TEXT("Ability [%s], Tag: %s, InputTag: %s"), *Ability->GetName(), *Tag.ToString(), *Ability->StartupInputTag.ToString());
	auto Info = AbilityInfo->GetAbilityInfo(Tag);
	Info.InputTag = Ability->StartupInputTag;

	OnAbilityInfoChanged(Info);
}