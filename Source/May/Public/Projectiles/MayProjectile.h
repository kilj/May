// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "MayProjectile.generated.h"

class UNiagaraSystem;
class UProjectileMovementComponent;
class USphereComponent;
class USoundBase;

UCLASS()
class MAY_API AMayProjectile : public AActor {
	GENERATED_BODY()

public:
	AMayProjectile();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageGESpecHandle;

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect; //TODO: get impact effect from OtherActor character's config

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound; //TODO: get impact sound from OtherActor character's config
	
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool bHit = false;
	void OnImpact() const;

};
