// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelInfo.generated.h"

class UMayGameplayAbility;

USTRUCT(BlueprintType)
struct FLevelInfoDefault {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Level = 0;

	// How many experience points character needs to achieve next level
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Experience = 100;

	// How many attribute points will be granted to character on current level
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 AttributePoints = 0;
	
	// These abilities will be granted to character on current level
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<UMayGameplayAbility>> Abilities;
};

/**
 * 
 */
UCLASS()
class MAY_API ULevelInfo : public UDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FLevelInfoDefault> Levels;

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UFUNCTION()
	FLevelInfoDefault GetLevelInfo(const float Level);

	UFUNCTION(BlueprintCallable)
	float GetLevel(const int32 Experience);

	UFUNCTION(BlueprintCallable)
	int32 GetExperience(const float Level);
};
