// Red Beat, 2023

#include "UI/Widget/StatusBarWidget.h"
#include "AbilitySystem/MayAttributeSet.h"
#include "AbilitySystem/MayGameplayTags.h"

void UStatusBarWidget::InitWidget(const FStatusBarWidgetData Data) {
	WidgetData = Data;


	SubscribeToAttribute(Data.AbilitySystemComponent, Data.AttributeSet, FMayGameplayTags::Get().AttributesSecondaryMaxHealth, Data.AttributeSet->GetMaxHealthAttribute());
	SubscribeToAttribute(Data.AbilitySystemComponent, Data.AttributeSet, FMayGameplayTags::Get().AttributesVitalHealth, Data.AttributeSet->GetHealthAttribute());

	BroadcastAttribute(Data.AttributeSet, FMayGameplayTags::Get().AttributesSecondaryMaxHealth, Data.AttributeSet->GetMaxHealthAttribute());
	BroadcastAttribute(Data.AttributeSet, FMayGameplayTags::Get().AttributesVitalHealth, Data.AttributeSet->GetHealthAttribute());

	OnWidgetInited();
}
