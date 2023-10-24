// Red Beat, 2023

#include "UI/Widget/MayWidget.h"

#include "AbilitySystem/MayAbilitySystemComponent.h"
#include "AbilitySystem/MayAttributeSet.h"
#include "AbilitySystem/MayGameplayTags.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UMayWidget::SubscribeToAttribute(UMayAbilitySystemComponent* ASC, UMayAttributeSet* AS, FGameplayTag AttributeTag, FGameplayAttribute Attribute) const {
	ASC->GetGameplayAttributeValueChangeDelegate(Attribute).AddLambda([this, AS, AttributeTag, Attribute](const FOnAttributeChangeData& Data)
	{
		auto Info = AttributeInfo->FindAttributeInfo(AttributeTag, true);
		Info.Value = Attribute.GetNumericValue(AS); //AS->GetArmor();
		AttributeInfoDelegate.Broadcast(Info);
	});
}

void UMayWidget::BroadcastAttribute(const UMayAttributeSet* AS, const FGameplayTag AttributeTag, const FGameplayAttribute& Attribute) const {
	auto Info = AttributeInfo->FindAttributeInfo(AttributeTag, true);
	Info.Value = Attribute.GetNumericValue(AS); //AS->GetArmor();
	AttributeInfoDelegate.Broadcast(Info);
}
