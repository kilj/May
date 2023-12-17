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

	//attributes.resistance
	Instance.AttributesResistancePhysical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Physical"));
	Instance.AttributesResistanceMagical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Magical"));

	//attributes.vital
	Instance.AttributesVitalHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"));
	Instance.AttributesVitalMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Mana"));

	//abilities
	Instance.Ability = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability"));
	Instance.AbilityAttackMelee = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.Attack.Melee"));
	Instance.AbilityAttackRanged = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.Attack.Ranged"));
	Instance.AbilitySpellFirebolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.Spell.Firebolt"));
	Instance.AbilitySpellSummon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Ability.Spell.Summon"));

	//cooldowns
	Instance.CooldownSpellFirebolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Spell.Firebolt"));

	//message
	Instance.MessageHealthCrystal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.HealthCrystal"));
	Instance.MessageHealthPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.HealthPotion"));
	Instance.MessageManaCrystal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.ManaCrystal"));
	Instance.MessageManaPotion = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Message.ManaPotion"));

	//sockets (for montages and cues)
	Instance.SocketWeapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Socket.Weapon"));
	Instance.SocketWeaponStuff = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Socket.Weapon.Stuff"));
	Instance.SocketWeaponStuffMelee = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Socket.Weapon.Stuff.Melee"));
	Instance.SocketWeaponStuffFirebolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Socket.Weapon.Stuff.Firebolt"));
	Instance.SocketWeaponAxe = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Socket.Weapon.Axe"));
	Instance.SocketWeaponSpear = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Socket.Weapon.Spear"));
	Instance.SocketWeaponSlingshot = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Socket.Weapon.Slingshot"));
	Instance.SocketHandR = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Socket.Hand.R"));
	Instance.SocketHandL = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Socket.Hand.L"));
	Instance.SocketTail = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Socket.Tail"));
	Instance.SocketSummon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Socket.Summon"));
	
	//input
	Instance.InputKeySpace = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Key.Space"));
	Instance.InputKeyLMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Key.LMB"));
	Instance.InputKeyRMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Key.RMB"));
	Instance.InputKey1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Key.1"));
	Instance.InputKey2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Key.2"));
	Instance.InputKey3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Key.3"));
	Instance.InputKey4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.Key.4"));

	//meta attributes
	Instance.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"), FString("Meta attribute for incoming damage"));
	Instance.Experience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Experience"), FString("Meta attribute for incoming experience"));

	//damage types
	Instance.DamageTypePhysical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Type.Physical"));
	Instance.DamageTypeMagicalFire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Type.Magical.Fire"));
	Instance.DamageTypeMagicalIce = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Type.Magical.Ice"));

	//damage type to resistant attribute map
	Instance.DamageTypes.Add(Instance.DamageTypePhysical, Instance.AttributesResistancePhysical);
	Instance.DamageTypes.Add(Instance.DamageTypeMagicalFire, Instance.AttributesResistanceMagical);
	Instance.DamageTypes.Add(Instance.DamageTypeMagicalIce, Instance.AttributesResistanceMagical);

	//effects
	Instance.EffectsHitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"));
	Instance.EffectsHitReactBlood = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact.Blood"));
}
