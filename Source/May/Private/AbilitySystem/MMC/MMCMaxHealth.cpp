// Red Beat, 2023

#include "AbilitySystem/MMC/MMCMaxHealth.h"
#include "AbilitySystem/MayAttributeSet.h"
#include "Character/Interfaces/LevelInterface.h"

UMMCMaxHealth::UMMCMaxHealth() {
	VigorDef.AttributeToCapture = UMayAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMCMaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const {
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters Params;
	Params.SourceTags = SourceTags;
	Params.TargetTags = TargetTags;

	float Vigor = 0.0f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, Params, Vigor);
	Vigor = FMath::Max<float>(Vigor, 0.0f);

	auto ILI = Cast<ILevelInterface>(Spec.GetContext().GetSourceObject());
	const int32 Level = ILI->GetLevel();

	return 80.f + 2.5f * Vigor + 10.f * Level;
}
