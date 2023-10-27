// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FMayAttributeInfo {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag Tag = FGameplayTag::EmptyTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description = FText();

	UPROPERTY(BlueprintReadOnly)
	float Value = 0.0f;
};

/**
 * 
 */
UCLASS()
class MAY_API UAttributeInfo : public UDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FMayAttributeInfo> Info; //TODO: convert to TMap<tag, info>

	FMayAttributeInfo FindAttributeInfo(const FGameplayTag& Tag, const bool bLogNotFound = false) const;
};
