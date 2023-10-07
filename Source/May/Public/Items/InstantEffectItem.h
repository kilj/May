#pragma once

#include "CoreMinimal.h"
#include "Items/MayItemBase.h"
#include "InstantEffectItem.generated.h"

class UGameplayEffect;

UCLASS()
class MAY_API AInstantEffectItem : public AMayItemBase {
	GENERATED_BODY()

public:
	AInstantEffectItem();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
};
