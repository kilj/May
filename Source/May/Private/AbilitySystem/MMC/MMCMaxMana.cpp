// Red Beat, 2023

#include "AbilitySystem/MMC/MMCMaxMana.h"

#include "AbilitySystem/MayAttributeSet.h"
#include "Character/Interfaces/LevelInterface.h"

UMMCMaxMana::UMMCMaxMana() {
	IntelligenceDef.AttributeToCapture = UMayAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false;
}

float UMMCMaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const {
	auto SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	auto TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters Params;
	Params.SourceTags = SourceTags;
	Params.TargetTags = TargetTags;

	float Intelligence = 0.0f;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, Params, Intelligence);
	Intelligence = FMath::Max(Intelligence, 0.0f);

	auto ILI = Cast<ILevelInterface>(Spec.GetContext().GetSourceObject());
	const int32 Level = ILI->GetLevel();

	return 50.0f + 2.0f * Intelligence + 5.0f * Level;
}
