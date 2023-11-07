// Red Beat, 2023

#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/MayAbilityTypes.h"
#include "AbilitySystem/MayAttributeSet.h"
#include "AbilitySystem/MayGameplayTags.h"

struct MayDamageStatics {
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	
	MayDamageStatics() {
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMayAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMayAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMayAttributeSet, ArmorPenetration, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMayAttributeSet, CriticalHitChance, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMayAttributeSet, CriticalHitDamage, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMayAttributeSet, CriticalHitResistance, Target, false);
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
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const {
	const auto SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const auto TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const auto SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const auto TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const auto Spec = ExecutionParams.GetOwningSpec();
	const auto EffectContext = static_cast<FMayGameplayEffectContext*>(Spec.GetContext().Get());

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters Params;
	Params.SourceTags = SourceTags;
	Params.TargetTags = TargetTags;

	//TODO: depend damage calculations from Source/Target level
	
	float Damage = 0.f;

	for (const auto& DamageType : FMayGameplayTags::Get().DamageTypes) {
		Damage += Spec.GetSetByCallerMagnitude(DamageType.Key, false);
	}

	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, Params, SourceCriticalHitChance);

	float SourceCriticalHitDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef, Params, SourceCriticalHitDamage);

	float TargetCriticalHitResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef, Params, TargetCriticalHitResistance);

	const bool bCriticalDamageHit = FMath::RandRange(0.f, 100.f) <= SourceCriticalHitChance;
	EffectContext->SetIsCriticalHit(bCriticalDamageHit);
	
	if (bCriticalDamageHit) {
		UE_LOG(LogTemp, Warning, TEXT("Critical hit! Source CritHitChance: %f"), SourceCriticalHitChance);
		Damage *= FMath::Max(1.f, 1.f + SourceCriticalHitDamage * 0.01f - TargetCriticalHitResistance * 0.01f);
	}

	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, Params, TargetBlockChance);

	const bool bBlockedHit = FMath::RandRange(0.f, 100.f) <= TargetBlockChance;
	EffectContext->SetIsBlockHit(bBlockedHit);

	if (bBlockedHit) {
		UE_LOG(LogTemp, Warning, TEXT("Hit successfully blocked! Target's block chance was %f"), TargetBlockChance);
		Damage *= 0.5f; //TODO: pass this value with SetByCallerMagnitude FMayGameplayTags::Get().DamageBlockMitigation OR make a CT in EnemyTypesInfo and get that value from it
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
