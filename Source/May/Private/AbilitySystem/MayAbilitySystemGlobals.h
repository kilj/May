// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "MayAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class MAY_API UMayAbilitySystemGlobals : public UAbilitySystemGlobals {
	GENERATED_BODY()

	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
