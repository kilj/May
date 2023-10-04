#pragma once

#include "CoreMinimal.h"
#include "Items/MayItemBase.h"
#include "HealthPotionTestItem.generated.h"

UCLASS()
class MAY_API AHealthPotionTestItem : public AMayItemBase {
	GENERATED_BODY()

public:
	AHealthPotionTestItem();

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
protected:
	virtual void BeginPlay() override;
};
