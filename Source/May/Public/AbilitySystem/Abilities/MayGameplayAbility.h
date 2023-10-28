// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MayGameplayAbility.generated.h"

/**
 * Base gameplay ability class for all abilities in May project
 */
UCLASS()
class MAY_API UMayGameplayAbility : public UGameplayAbility {
	GENERATED_BODY()

public:
	// Ability's tags can be changed since game started, so we'll use this tag for character's startup abilities
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;

	// This will NOT be used for non-damage abilities. TODO: move to subclass or ability subcomponent if needed 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage")
	FScalableFloat Damage;
};
