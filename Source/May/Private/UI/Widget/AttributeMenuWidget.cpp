// Red Beat, 2023

#include "UI/Widget/AttributeMenuWidget.h"
#include "AbilitySystem/MayAttributeSet.h"
#include "AbilitySystem/MayGameplayTags.h"

void UAttributeMenuWidget::InitWidget(const FAttributeMenuWidgetData Data) {
	WidgetData = Data;

	const auto ASC = Data.AbilitySystemComponent;
	const auto AS = Data.AttributeSet;

	//primary
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesPrimaryStrength, Data.AttributeSet->GetStrengthAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesPrimaryIntelligence, Data.AttributeSet->GetIntelligenceAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesPrimaryResilience, Data.AttributeSet->GetResilienceAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesPrimaryVigor, Data.AttributeSet->GetVigorAttribute());

	//secondary
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryArmor, Data.AttributeSet->GetArmorAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryArmorPenetration, Data.AttributeSet->GetArmorPenetrationAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryBlockChance, Data.AttributeSet->GetBlockChanceAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryCriticalHitChance, Data.AttributeSet->GetCriticalHitChanceAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryCriticalHitDamage, Data.AttributeSet->GetCriticalHitDamageAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryCriticalHitResistance, Data.AttributeSet->GetCriticalHitResistanceAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryHealthRegeneration, Data.AttributeSet->GetHealthRegenerationAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryManaRegeneration, Data.AttributeSet->GetManaRegenerationAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryMaxHealth, Data.AttributeSet->GetMaxHealthAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryMaxMana, Data.AttributeSet->GetMaxManaAttribute());

	//TODO: vital

	//broadcasting
	BroadcastAttribute(Data.AttributeSet, FMayGameplayTags::Get().AttributesPrimaryStrength, Data.AttributeSet->GetStrengthAttribute());
	BroadcastAttribute(Data.AttributeSet, FMayGameplayTags::Get().AttributesPrimaryIntelligence, Data.AttributeSet->GetIntelligenceAttribute());
	BroadcastAttribute(Data.AttributeSet, FMayGameplayTags::Get().AttributesPrimaryResilience, Data.AttributeSet->GetResilienceAttribute());
	BroadcastAttribute(Data.AttributeSet, FMayGameplayTags::Get().AttributesPrimaryVigor, Data.AttributeSet->GetVigorAttribute());

	BroadcastAttribute(Data.AttributeSet, FMayGameplayTags::Get().AttributesSecondaryArmor, Data.AttributeSet->GetArmorAttribute());
	BroadcastAttribute(Data.AttributeSet, FMayGameplayTags::Get().AttributesSecondaryArmorPenetration, Data.AttributeSet->GetArmorPenetrationAttribute());
	BroadcastAttribute(Data.AttributeSet, FMayGameplayTags::Get().AttributesSecondaryBlockChance, Data.AttributeSet->GetBlockChanceAttribute());
	BroadcastAttribute(Data.AttributeSet, FMayGameplayTags::Get().AttributesSecondaryCriticalHitChance, Data.AttributeSet->GetCriticalHitChanceAttribute());
	BroadcastAttribute(Data.AttributeSet, FMayGameplayTags::Get().AttributesSecondaryCriticalHitDamage, Data.AttributeSet->GetCriticalHitDamageAttribute());
	BroadcastAttribute(Data.AttributeSet, FMayGameplayTags::Get().AttributesSecondaryCriticalHitResistance, Data.AttributeSet->GetCriticalHitResistanceAttribute());
	BroadcastAttribute(Data.AttributeSet, FMayGameplayTags::Get().AttributesSecondaryHealthRegeneration, Data.AttributeSet->GetHealthRegenerationAttribute());
	BroadcastAttribute(Data.AttributeSet, FMayGameplayTags::Get().AttributesSecondaryManaRegeneration, Data.AttributeSet->GetManaRegenerationAttribute());
	BroadcastAttribute(Data.AttributeSet, FMayGameplayTags::Get().AttributesSecondaryMaxHealth, Data.AttributeSet->GetMaxHealthAttribute());
	BroadcastAttribute(Data.AttributeSet, FMayGameplayTags::Get().AttributesSecondaryMaxMana, Data.AttributeSet->GetMaxManaAttribute());

	//TODO: broadcast vital
	
	OnWidgetInited();
}
