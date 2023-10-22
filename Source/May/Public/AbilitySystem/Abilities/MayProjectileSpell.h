// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "MayGameplayAbility.h"
#include "MayProjectileSpell.generated.h"

class AMayProjectile;

/**
 * Ability which spawns MayProjectile and attaches to it "damage" GE
 */
UCLASS()
class MAY_API UMayProjectileSpell : public UMayGameplayAbility {
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AMayProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass; //TODO: rename to ImpactEffect?

	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FVector& TargetLocation);
	
};
