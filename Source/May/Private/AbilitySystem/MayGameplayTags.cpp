// Red Beat, 2023

#include "AbilitySystem/MayGameplayTags.h"
#include "GameplayTagsManager.h"

FMayGameplayTags FMayGameplayTags::Instance;

void FMayGameplayTags::InitNativeGameplayTags() {
	Instance.AttributesPrimaryStrength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"));
	Instance.AttributesPrimaryIntelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"));
	Instance.AttributesPrimaryResilience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"));
	Instance.AttributesPrimaryVigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"));

	Instance.AttributesSecondaryArmor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"));
	Instance.AttributesSecondaryArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"));
	Instance.AttributesSecondaryBlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"));
	Instance.AttributesSecondaryCriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"));
	Instance.AttributesSecondaryCriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"));
	Instance.AttributesSecondaryCriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"));
	Instance.AttributesSecondaryHealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"));
	Instance.AttributesSecondaryManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"));
	Instance.AttributesSecondaryMaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"));
	Instance.AttributesSecondaryMaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"));
	
	Instance.AttributesVitalHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"));
	Instance.AttributesVitalMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Mana"));

	//message
	Instance.MessageHealthCrystal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.HealthCrystal"));
	Instance.MessageHealthPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.HealthPotion"));
	Instance.MessageManaCrystal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.ManaCrystal"));
	Instance.MessageManaPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.ManaPotion"));

	//event
	Instance.EventMontageFirebolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Montage.Firebolt"));
	
	//input
	Instance.InputKeyLMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Key.LMB"));
	Instance.InputKeyRMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Key.RMB"));
	Instance.InputKey1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Key.1"));
	Instance.InputKey2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Key.2"));
	Instance.InputKey3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Key.3"));
	Instance.InputKey4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Key.4"));
}
