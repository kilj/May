// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "MayGameplayAbility.h"
#include "MayDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class MAY_API UMayDamageGameplayAbility : public UMayGameplayAbility {
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass; //TODO: rename to ImpactEffect?

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
