// Red Beat, 2023

#include "UI/Widget/MayWidget.h"

#include "AbilitySystem/MayAbilitySystemComponent.h"
#include "AbilitySystem/MayAttributeSet.h"
#include "AbilitySystem/MayGameplayTags.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UMayWidget::SubscribeToAttribute(UMayAbilitySystemComponent* ASC, UMayAttributeSet* AS, FGameplayTag AttributeTag, const FGameplayAttribute& Attribute) {
	ASC->GetGameplayAttributeValueChangeDelegate(Attribute).AddLambda([this, AttributeTag](const FOnAttributeChangeData& Data)
	{
		auto Info = AttributeInfo->FindAttributeInfo(AttributeTag, true);
		Info.Value = Data.NewValue;
		OnAttributeInfoChanged(Info);
	});
}

void UMayWidget::BroadcastAttribute(const UMayAttributeSet* AS, const FGameplayTag AttributeTag, const FGameplayAttribute& Attribute) {
	auto Info = AttributeInfo->FindAttributeInfo(AttributeTag, true);
	Info.Value = Attribute.GetNumericValue(AS); //AS->GetArmor();
	OnAttributeInfoChanged(Info);
}
