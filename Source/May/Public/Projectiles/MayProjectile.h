// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MayProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class MAY_API AMayProjectile : public AActor {
	GENERATED_BODY()

public:
	AMayProjectile();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
