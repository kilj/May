// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "MayDamageGameplayAbility.h"
#include "MayProjectileSpell.generated.h"

class AMayProjectile;

/**
 * Ability which spawns MayProjectile and attaches to it "damage" GE
 */
UCLASS()
class MAY_API UMayProjectileSpell : public UMayDamageGameplayAbility {
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AMayProjectile> ProjectileClass;

	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FVector& TargetLocation);
	
};
