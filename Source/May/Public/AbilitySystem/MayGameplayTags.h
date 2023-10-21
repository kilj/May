// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * Singleton
 */
struct FMayGameplayTags {
	static const FMayGameplayTags& Get() { return Instance; }

	static void InitNativeGameplayTags();

	//attributes.primary
	FGameplayTag AttributesPrimaryStrength;
	FGameplayTag AttributesPrimaryIntelligence;
	FGameplayTag AttributesPrimaryResilience;
	FGameplayTag AttributesPrimaryVigor;

	//attributes.secondary
	FGameplayTag AttributesSecondaryArmor;
	FGameplayTag AttributesSecondaryArmorPenetration;
	FGameplayTag AttributesSecondaryBlockChance;
	FGameplayTag AttributesSecondaryCriticalHitChance;
	FGameplayTag AttributesSecondaryCriticalHitDamage;
	FGameplayTag AttributesSecondaryCriticalHitResistance;
	FGameplayTag AttributesSecondaryHealthRegeneration;
	FGameplayTag AttributesSecondaryManaRegeneration;
	FGameplayTag AttributesSecondaryMaxHealth;
	FGameplayTag AttributesSecondaryMaxMana;

	//attributes.vital
	FGameplayTag AttributesVitalHealth;
	FGameplayTag AttributesVitalMana;

	//message
	FGameplayTag MessageHealthCrystal;
	FGameplayTag MessageHealthPotion;
	FGameplayTag MessageManaCrystal;
	FGameplayTag MessageManaPotion;

	//events.montage
	FGameplayTag EventMontageFirebolt;

	//input
	FGameplayTag InputKeyLMB;
	FGameplayTag InputKeyRMB;
	FGameplayTag InputKey1;
	FGameplayTag InputKey2;
	FGameplayTag InputKey3;
	FGameplayTag InputKey4;

private:
	static FMayGameplayTags Instance;
};
