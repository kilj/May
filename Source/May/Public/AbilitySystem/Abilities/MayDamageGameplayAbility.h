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
	TMap<FGameplayTag, FScalableFloat> DamageTypes; //theoretically, game-designer can add ANY tag here as damage type and it will be an error in future damage calculations. TODO: we must limit/validate possible tags or wrap tags to enum
};
