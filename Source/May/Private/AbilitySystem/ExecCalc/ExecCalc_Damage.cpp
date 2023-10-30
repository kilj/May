// Red Beat, 2023

#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/MayAttributeSet.h"
#include "AbilitySystem/MayGameplayTags.h"

struct MayDamageStatics {
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	
	MayDamageStatics() {
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMayAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMayAttributeSet, BlockChance, Target, false);
	}
};

static const MayDamageStatics& DamageStatics() {
	static MayDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage() {
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const {
	const auto SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const auto TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const auto SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const auto TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const auto Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters Params;
	Params.SourceTags = SourceTags;
	Params.TargetTags = TargetTags;

	float Damage = Spec.GetSetByCallerMagnitude(FMayGameplayTags::Get().Damage);

	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, Params, TargetBlockChance);

	const auto BlockRandom = FMath::RandRange(0.f, 100.f);
	UE_LOG(LogTemp, Log, TEXT("Eval block: BlockRandom: %f, BlockChance: %f"), BlockRandom, TargetBlockChance);
	if (BlockRandom <= TargetBlockChance) {
		UE_LOG(LogTemp, Warning, TEXT("Successful block! BlockRandom: %f, BlockChance: %f"), BlockRandom, TargetBlockChance);
		Damage *= 0.5f;
	}
	
	//TODO: clamp if needed

	const FGameplayModifierEvaluatedData EvaluatedData(UMayAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
