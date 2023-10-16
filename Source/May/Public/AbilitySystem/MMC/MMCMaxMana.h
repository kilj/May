// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMCMaxMana.generated.h"

/**
 * 
 */
UCLASS()
class MAY_API UMMCMaxMana : public UGameplayModMagnitudeCalculation {
	GENERATED_BODY()

public:
	UMMCMaxMana();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition IntelligenceDef;
};
