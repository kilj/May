// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMCMaxHealth.generated.h"

/**
 * 
 */
UCLASS()
class MAY_API UMMCMaxHealth : public UGameplayModMagnitudeCalculation {
	GENERATED_BODY()

public:
	UMMCMaxHealth();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition VigorDef;
};
