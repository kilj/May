// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "MayGameplayAbility.h"
#include "MayProjectileSpell.generated.h"

class AMayProjectile;

/**
 * 
 */
UCLASS()
class MAY_API UMayProjectileSpell : public UMayGameplayAbility {
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AMayProjectile> ProjectileClass;

	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FVector& TargetLocation);
	
};
