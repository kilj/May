// Red Beat, 2023

#include "UI/Widget/OverlayWidget.h"

#include "AbilitySystem/MayAbilitySystemComponent.h"
#include "AbilitySystem/MayAttributeSet.h"
#include "AbilitySystem/MayGameplayTags.h"

void UOverlayWidget::InitWidget(const FOverlayWidgetData Data) {
	WidgetData = Data;

	const auto ASC = Data.AbilitySystemComponent;
	const auto AS = Data.AttributeSet;
	
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryMaxHealth, Data.AttributeSet->GetMaxHealthAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesVitalHealth, Data.AttributeSet->GetHealthAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryMaxMana, Data.AttributeSet->GetMaxManaAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesVitalMana, Data.AttributeSet->GetManaAttribute());

	BroadcastAttribute(AS, FMayGameplayTags::Get().AttributesSecondaryMaxHealth, Data.AttributeSet->GetMaxHealthAttribute());
	BroadcastAttribute(AS, FMayGameplayTags::Get().AttributesVitalHealth, Data.AttributeSet->GetHealthAttribute());
	BroadcastAttribute(AS, FMayGameplayTags::Get().AttributesSecondaryMaxMana, Data.AttributeSet->GetMaxManaAttribute());
	BroadcastAttribute(AS, FMayGameplayTags::Get().AttributesVitalMana, Data.AttributeSet->GetManaAttribute());

	ASC->EffectAssetTagsDelegate.AddUObject(this, &ThisClass::GameplayEffectAssetTagApplied);
	
	OnWidgetInited();
}

void UOverlayWidget::GameplayEffectAssetTagApplied(const FGameplayTagContainer& Data) {
	for (const auto Tag : Data) {
		if (!Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Message"))))
			continue;
		
		const auto Row = GetDataTableRowByTag<FUINotificationWidgetRow>(NotificationsWidgetDataTable, Tag);
		OnUINotificationMessage(*Row);
	}
}
