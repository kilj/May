// Red Beat, 2023

#include "UI/Widget/AttributeMenuWidget.h"

#include "AbilitySystem/MayAbilitySystemComponent.h"
#include "AbilitySystem/MayAttributeSet.h"
#include "AbilitySystem/MayGameplayTags.h"
#include "Player/EnniePlayerState.h"

void UAttributeMenuWidget::InitWidget(const FAttributeMenuWidgetData Data) {
	WidgetData = Data;

	const auto ASC = Cast<UMayAbilitySystemComponent>(Data.PlayerState->GetAbilitySystemComponent());
	const auto AS = Cast<UMayAttributeSet>(Data.PlayerState->GetAttributeSet());

	//primary
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesPrimaryStrength, AS->GetStrengthAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesPrimaryIntelligence, AS->GetIntelligenceAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesPrimaryResilience, AS->GetResilienceAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesPrimaryVigor, AS->GetVigorAttribute());

	//secondary
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryArmor, AS->GetArmorAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryArmorPenetration, AS->GetArmorPenetrationAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryBlockChance, AS->GetBlockChanceAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryCriticalHitChance, AS->GetCriticalHitChanceAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryCriticalHitDamage, AS->GetCriticalHitDamageAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryCriticalHitResistance, AS->GetCriticalHitResistanceAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryHealthRegeneration, AS->GetHealthRegenerationAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryManaRegeneration, AS->GetManaRegenerationAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryMaxHealth, AS->GetMaxHealthAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesSecondaryMaxMana, AS->GetMaxManaAttribute());

	//resistances
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesResistancePhysical, AS->GetResistancePhysicalAttribute());
	SubscribeToAttribute(ASC, AS, FMayGameplayTags::Get().AttributesResistanceMagical, AS->GetResistanceMagicalAttribute());

	//TODO: vital

	//broadcasting
	BroadcastAttribute(AS, FMayGameplayTags::Get().AttributesPrimaryStrength, AS->GetStrengthAttribute());
	BroadcastAttribute(AS, FMayGameplayTags::Get().AttributesPrimaryIntelligence, AS->GetIntelligenceAttribute());
	BroadcastAttribute(AS, FMayGameplayTags::Get().AttributesPrimaryResilience, AS->GetResilienceAttribute());
	BroadcastAttribute(AS, FMayGameplayTags::Get().AttributesPrimaryVigor, AS->GetVigorAttribute());

	BroadcastAttribute(AS, FMayGameplayTags::Get().AttributesSecondaryArmor, AS->GetArmorAttribute());
	BroadcastAttribute(AS, FMayGameplayTags::Get().AttributesSecondaryArmorPenetration, AS->GetArmorPenetrationAttribute());
	BroadcastAttribute(AS, FMayGameplayTags::Get().AttributesSecondaryBlockChance, AS->GetBlockChanceAttribute());
	BroadcastAttribute(AS, FMayGameplayTags::Get().AttributesSecondaryCriticalHitChance, AS->GetCriticalHitChanceAttribute());
	BroadcastAttribute(AS, FMayGameplayTags::Get().AttributesSecondaryCriticalHitDamage, AS->GetCriticalHitDamageAttribute());
	BroadcastAttribute(AS, FMayGameplayTags::Get().AttributesSecondaryCriticalHitResistance, AS->GetCriticalHitResistanceAttribute());
	BroadcastAttribute(AS, FMayGameplayTags::Get().AttributesSecondaryHealthRegeneration, AS->GetHealthRegenerationAttribute());
	BroadcastAttribute(AS, FMayGameplayTags::Get().AttributesSecondaryManaRegeneration, AS->GetManaRegenerationAttribute());
	BroadcastAttribute(AS, FMayGameplayTags::Get().AttributesSecondaryMaxHealth, AS->GetMaxHealthAttribute());
	BroadcastAttribute(AS, FMayGameplayTags::Get().AttributesSecondaryMaxMana, AS->GetMaxManaAttribute());
	
	BroadcastAttribute(AS, FMayGameplayTags::Get().AttributesResistancePhysical, AS->GetResistancePhysicalAttribute());
	BroadcastAttribute(AS, FMayGameplayTags::Get().AttributesResistanceMagical, AS->GetResistanceMagicalAttribute());

	//TODO: broadcast vital

	OnAttributePointsChanged(Data.PlayerState->AttributePoints);
	OnSpellPointsChanged(Data.PlayerState->SpellPoints);
	
	OnWidgetInited();
}
