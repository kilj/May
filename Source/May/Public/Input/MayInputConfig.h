// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "MayInputConfig.generated.h"

USTRUCT(BlueprintType)
struct FMayInputAction {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* Action = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag Tag = FGameplayTag();
};

/**
 * 
 */
UCLASS()
class MAY_API UMayInputConfig : public UDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FMayInputAction> AbilityInputActions;

	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& Tag, const bool bLogNotFound = false) const;
	
};
