// Red Beat, 2023


#include "UI/WIdgetController/AttributeWindowWidgetController.h"
#include "AbilitySystem/MayAttributeSet.h"
#include "AbilitySystem/MayGameplayTags.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeWindowWidgetController::BroadcastInitialValues() {
	Super::BroadcastInitialValues();

	const auto AS = CastChecked<UMayAttributeSet>(AttributeSet);

	check(AttributeInfo);

	//primary
	auto Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesPrimaryStrength, true);
	Info.Value = AS->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);

	Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesPrimaryIntelligence, true);
	Info.Value = AS->GetIntelligence();
	AttributeInfoDelegate.Broadcast(Info);

	Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesPrimaryResilience, true);
	Info.Value = AS->GetResilience();
	AttributeInfoDelegate.Broadcast(Info);

	Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesPrimaryVigor, true);
	Info.Value = AS->GetVigor();
	AttributeInfoDelegate.Broadcast(Info);

	//secondary
	Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesSecondaryArmor, true);
	Info.Value = AS->GetArmor();
	AttributeInfoDelegate.Broadcast(Info);

	Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesSecondaryArmorPenetration, true);
	Info.Value = AS->GetArmorPenetration();
	AttributeInfoDelegate.Broadcast(Info);

	Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesSecondaryBlockChance, true);
	Info.Value = AS->GetBlockChance();
	AttributeInfoDelegate.Broadcast(Info);

	Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesSecondaryCriticalHitChance, true);
	Info.Value = AS->GetCriticalHitChance();
	AttributeInfoDelegate.Broadcast(Info);

	Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesSecondaryCriticalHitDamage, true);
	Info.Value = AS->GetCriticalHitDamage();
	AttributeInfoDelegate.Broadcast(Info);

	Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesSecondaryCriticalHitResistance, true);
	Info.Value = AS->GetCriticalHitResistance();
	AttributeInfoDelegate.Broadcast(Info);

	Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesSecondaryHealthRegeneration, true);
	Info.Value = AS->GetHealthRegeneration();
	AttributeInfoDelegate.Broadcast(Info);

	Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesSecondaryManaRegeneration, true);
	Info.Value = AS->GetManaRegeneration();
	AttributeInfoDelegate.Broadcast(Info);
	
	Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesSecondaryMaxHealth, true);
	Info.Value = AS->GetMaxHealth();
	AttributeInfoDelegate.Broadcast(Info);

	Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesSecondaryMaxMana, true);
	Info.Value = AS->GetMaxMana();
	AttributeInfoDelegate.Broadcast(Info);
}

void UAttributeWindowWidgetController::BindCallbacksToDependencies() {
	Super::BindCallbacksToDependencies();

	const auto AS = CastChecked<UMayAttributeSet>(AttributeSet);

	//primary attribute bindings
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetStrengthAttribute()).AddLambda([this, AS](const FOnAttributeChangeData& Data)
	{
		auto Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesPrimaryStrength, true);
		Info.Value = AS->GetStrength();
		AttributeInfoDelegate.Broadcast(Info);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetIntelligenceAttribute()).AddLambda([this, AS](const FOnAttributeChangeData& Data)
	{
		auto Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesPrimaryIntelligence, true);
		Info.Value = AS->GetIntelligence();
		AttributeInfoDelegate.Broadcast(Info);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetResilienceAttribute()).AddLambda([this, AS](const FOnAttributeChangeData& Data)
	{
		auto Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesPrimaryResilience, true);
		Info.Value = AS->GetResilience();
		AttributeInfoDelegate.Broadcast(Info);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetVigorAttribute()).AddLambda([this, AS](const FOnAttributeChangeData& Data)
	{
		auto Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesPrimaryVigor, true);
		Info.Value = AS->GetVigor();
		AttributeInfoDelegate.Broadcast(Info);
	});

	//secondary attribute bindings
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetArmorAttribute()).AddLambda([this, AS](const FOnAttributeChangeData& Data)
	{
		auto Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesSecondaryArmor, true);
		Info.Value = AS->GetArmor();
		AttributeInfoDelegate.Broadcast(Info);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetArmorPenetrationAttribute()).AddLambda([this, AS](const FOnAttributeChangeData& Data)
	{
		auto Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesSecondaryArmorPenetration, true);
		Info.Value = AS->GetArmorPenetration();
		AttributeInfoDelegate.Broadcast(Info);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetBlockChanceAttribute()).AddLambda([this, AS](const FOnAttributeChangeData& Data)
	{
		auto Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesSecondaryBlockChance, true);
		Info.Value = AS->GetBlockChance();
		AttributeInfoDelegate.Broadcast(Info);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetCriticalHitChanceAttribute()).AddLambda([this, AS](const FOnAttributeChangeData& Data)
	{
		auto Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesSecondaryCriticalHitChance, true);
		Info.Value = AS->GetCriticalHitChance();
		AttributeInfoDelegate.Broadcast(Info);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetCriticalHitDamageAttribute()).AddLambda([this, AS](const FOnAttributeChangeData& Data)
	{
		auto Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesSecondaryCriticalHitDamage, true);
		Info.Value = AS->GetCriticalHitDamage();
		AttributeInfoDelegate.Broadcast(Info);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetCriticalHitResistanceAttribute()).AddLambda([this, AS](const FOnAttributeChangeData& Data)
	{
		auto Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesSecondaryCriticalHitResistance, true);
		Info.Value = AS->GetCriticalHitResistance();
		AttributeInfoDelegate.Broadcast(Info);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetHealthRegenerationAttribute()).AddLambda([this, AS](const FOnAttributeChangeData& Data)
	{
		auto Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesSecondaryHealthRegeneration, true);
		Info.Value = AS->GetHealthRegeneration();
		AttributeInfoDelegate.Broadcast(Info);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetManaRegenerationAttribute()).AddLambda([this, AS](const FOnAttributeChangeData& Data)
	{
		auto Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesSecondaryManaRegeneration, true);
		Info.Value = AS->GetManaRegeneration();
		AttributeInfoDelegate.Broadcast(Info);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHealthAttribute()).AddLambda([this, AS](const FOnAttributeChangeData& Data)
	{
		auto Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesSecondaryMaxHealth, true);
		Info.Value = AS->GetMaxHealth();
		AttributeInfoDelegate.Broadcast(Info);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxManaAttribute()).AddLambda([this, AS](const FOnAttributeChangeData& Data)
	{
		auto Info = AttributeInfo->FindAttributeInfo(FMayGameplayTags::Get().AttributesSecondaryMaxMana, true);
		Info.Value = AS->GetMaxMana();
		AttributeInfoDelegate.Broadcast(Info);
	});



}