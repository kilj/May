// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyTypeInfo.generated.h"

class UGameplayAbility;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEnemyType : uint8 {
	GoblinMelee,
	GoblinArcher,
	GoblinShaman
};

USTRUCT()
struct FEnemyTypeDefaultInfo {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category="Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category="Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributes;
	
};

/**
 * 
 */
UCLASS()
class MAY_API UEnemyTypeInfo : public UDataAsset {
	GENERATED_BODY()

public:
	// common attributes for all classes
	// UPROPERTY(EditDefaultsOnly, Category="Defaults")
	// TSubclassOf<UGameplayEffect> SecondaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category="Defaults")
	TMap<EEnemyType, FEnemyTypeDefaultInfo> Info;

	// Common abilities for all enemy types (death, hitReact, etc)
	UPROPERTY(EditDefaultsOnly, Category="Defaults|Common")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;

	FEnemyTypeDefaultInfo GetEnemyTypeDefaultInfo(EEnemyType Type);
};
