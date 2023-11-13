// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MayGameplayAbility.generated.h"

class AMayProjectile;

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

	// Spawns projectile and attached to it impact GE (damage, attribute changing, etc)
	UFUNCTION(BlueprintCallable)
	void SpawnProjectileAndAttachEffect(TSubclassOf<AMayProjectile> ProjectileClass, TSubclassOf<UGameplayEffect> ImpactGEClass, TMap<FGameplayTag, FScalableFloat> DamageTypes, const FVector& SpawnLocation, const FVector& TargetLocation);

	// Apply GE to target actors
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToActors(TArray<AActor*> TargetActors, TSubclassOf<UGameplayEffect> ImpactGEClass, TMap<FGameplayTag, FScalableFloat> DamageTypes);

	// Apply GE to targetActor
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToActor(AActor* TargetActor, TSubclassOf<UGameplayEffect> ImpactGEClass, TMap<FGameplayTag, FScalableFloat> DamageTypes);
};
