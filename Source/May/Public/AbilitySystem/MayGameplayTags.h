// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * Singleton
 */
struct FMayGameplayTags {
public:
 static const FMayGameplayTags& Get() { return Instance; }

 static void InitNativeGameplayTags();

 FGameplayTag AttributesPrimaryStrength;
 FGameplayTag AttributesPrimaryIntelligence;
 FGameplayTag AttributesPrimaryResilience;
 FGameplayTag AttributesPrimaryVigor;

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
 
 FGameplayTag AttributesVitalHealth;
 FGameplayTag AttributesVitalMana;
 
 FGameplayTag MessageHealthCrystal;
 FGameplayTag MessageHealthPotion;
 FGameplayTag MessageManaCrystal;
 FGameplayTag MessageManaPotion;
 
protected:
private:
 static FMayGameplayTags Instance;
};
