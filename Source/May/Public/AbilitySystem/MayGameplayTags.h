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

	//attributes.resistance
	FGameplayTag AttributesResistancePhysical;
	FGameplayTag AttributesResistanceMagical;
	
	//attributes.vital
	FGameplayTag AttributesVitalHealth;
	FGameplayTag AttributesVitalMana;

	//abilities
	FGameplayTag Ability;
	FGameplayTag AbilityAttackMelee;
	FGameplayTag AbilityAttackRanged;
	FGameplayTag AbilitySpellFirebolt;
	FGameplayTag AbilitySpellSummon; //TODO: add Summon.Demon, Summon.Goblin, etc

	//cooldowns
	FGameplayTag CooldownSpellFirebolt;

	//message
	FGameplayTag MessageHealthCrystal;
	FGameplayTag MessageHealthPotion;
	FGameplayTag MessageManaCrystal;
	FGameplayTag MessageManaPotion;

	//sockets (for montages and cues)
	FGameplayTag SocketWeapon;
	FGameplayTag SocketWeaponStuff;
	FGameplayTag SocketWeaponStuffMelee;
	FGameplayTag SocketWeaponStuffFirebolt;
	FGameplayTag SocketWeaponAxe;
	FGameplayTag SocketWeaponSpear;
	FGameplayTag SocketWeaponSlingshot;
	FGameplayTag SocketHandR;
	FGameplayTag SocketHandL;
	FGameplayTag SocketTail;
	FGameplayTag SocketSummon; //TODO: in fact, this isn't a socket, but we're using socket-tags to identify correct data for abilities

	//input
	FGameplayTag InputKeySpace;
	FGameplayTag InputKeyLMB;
	FGameplayTag InputKeyRMB;
	FGameplayTag InputKey1;
	FGameplayTag InputKey2;
	FGameplayTag InputKey3;
	FGameplayTag InputKey4;

	//meta
	FGameplayTag Damage;
	FGameplayTag Experience;

	//damageTypes
	FGameplayTag DamageTypePhysical;
	FGameplayTag DamageTypeMagicalFire;
	FGameplayTag DamageTypeMagicalIce;

	TMap<FGameplayTag, FGameplayTag> DamageTypes; //damagetype -> resistance

	//effects
	FGameplayTag EffectsHitReact;
	FGameplayTag EffectsHitReactBlood;

private:
	static FMayGameplayTags Instance;
};
