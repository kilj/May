#include "UI/WIdgetController/OverlayWidgetController.h"

#include "AbilitySystem/MayAbilitySystemComponent.h"
#include "AbilitySystem/MayAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues() {
	Super::BroadcastInitialValues();

	const auto AS = CastChecked<UMayAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(AS->GetHealth());
	OnMaxHealthChanged.Broadcast(AS->GetMaxHealth());
	OnManaChanged.Broadcast(AS->GetMana());
	OnMaxManaChanged.Broadcast(AS->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies() {
	Super::BindCallbacksToDependencies();

	const auto AS = CastChecked<UMayAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data){OnHealthChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& Data){OnMaxHealthChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data){OnManaChanged.Broadcast(Data.NewValue);});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxManaAttribute()).AddLambda([this](const FOnAttributeChangeData& Data){OnMaxManaChanged.Broadcast(Data.NewValue);});

	const auto ASC = CastChecked<UMayAbilitySystemComponent>(AbilitySystemComponent);
	ASC->EffectAssetTagsDelegate.AddUObject(this, &UOverlayWidgetController::GameplayEffectAssetTagApplied);
	
}

void UOverlayWidgetController::GameplayEffectAssetTagApplied(const FGameplayTagContainer& Data) {
	for (const auto Tag : Data) {
		if (!Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Message"))))
			continue;
		
		const auto Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
		MessageWidgetRowDelegate.Broadcast(*Row);
	}
}
