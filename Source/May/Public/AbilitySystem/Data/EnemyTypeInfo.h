// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "ScalableFloat.h"
#include "Engine/DataAsset.h"
#include "EnemyTypeInfo.generated.h"

class UGameplayAbility;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEnemyType : uint8 {
	None,
	GoblinMelee,
	GoblinArcher,
	GoblinShaman,
	Ghoul,
	Demon
};

UENUM(BlueprintType, Blueprintable)
enum class EEnemyAttackType : uint8 {
	Melee,
	Ranged
};

USTRUCT(BlueprintType)
struct FEnemyTypeDefaultInfo {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Defaults")
	EEnemyAttackType AttackType = EEnemyAttackType::Melee;

	UPROPERTY(EditDefaultsOnly, Category="Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category="Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category="Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributes;

	UPROPERTY(EditDefaultsOnly, Category="Defaults")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;

	// Amount of experience, which will be granted to other character for killing this character. Note: fraction part of value will be ignored (e.g. 3.9 will handled as 3.0)
	UPROPERTY(EditDefaultsOnly, Category="Defaults")
	FScalableFloat Experience;
};

/**
 * 
 */
UCLASS()
class MAY_API UEnemyTypeInfo : public UDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Defaults")
	TMap<EEnemyType, FEnemyTypeDefaultInfo> Info;

	// Common abilities for all enemy types (death, hitReact, etc)
	UPROPERTY(EditDefaultsOnly, Category="Defaults|Common")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;

	FEnemyTypeDefaultInfo GetEnemyTypeDefaultInfo(EEnemyType Type);
};
