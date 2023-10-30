// Red Beat, 2023

#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/MayAttributeSet.h"
#include "AbilitySystem/MayGameplayTags.h"

struct MayDamageStatics {
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	
	MayDamageStatics() {
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMayAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMayAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMayAttributeSet, ArmorPenetration, Source, true);
	}
};

static const MayDamageStatics& DamageStatics() {
	static MayDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage() {
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
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
		Damage *= 0.5f; //TODO: pass this value with SetByCallerMagnitude FMayGameplayTags::Get().DamageBlockMitigation
	}

	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, Params, TargetArmor);

	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, Params, SourceArmorPenetration);
	
	//that's pretty volatile code and I've wrote it here just to do at least something
	const float EffectiveArmor = TargetArmor *= (100 - SourceArmorPenetration * 0.25f) * 0.01f;
	Damage *= (100 - EffectiveArmor * 0.5f) * 0.01f;
	//end

	const FGameplayModifierEvaluatedData EvaluatedData(UMayAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
