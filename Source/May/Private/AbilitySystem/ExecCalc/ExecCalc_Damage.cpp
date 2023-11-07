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
	
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistancePhysical);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistanceMagical);

	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	
	MayDamageStatics() {
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMayAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMayAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMayAttributeSet, ArmorPenetration, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMayAttributeSet, CriticalHitChance, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMayAttributeSet, CriticalHitDamage, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMayAttributeSet, CriticalHitResistance, Target, false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMayAttributeSet, ResistancePhysical, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMayAttributeSet, ResistanceMagical, Target, false);

		TagsToCaptureDefs.Add(FMayGameplayTags::Get().DamagePhysical, ResistancePhysicalDef);
		TagsToCaptureDefs.Add(FMayGameplayTags::Get().DamagePhysicalBleeding, ResistancePhysicalDef);
		TagsToCaptureDefs.Add(FMayGameplayTags::Get().DamageMagicFire, ResistanceMagicalDef);
		TagsToCaptureDefs.Add(FMayGameplayTags::Get().DamageMagicIce, ResistanceMagicalDef);
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
	
	RelevantAttributesToCapture.Add(DamageStatics().ResistancePhysicalDef);
	RelevantAttributesToCapture.Add(DamageStatics().ResistanceMagicalDef);
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

	for (const auto& Pair : FMayGameplayTags::Get().DamageTypes) {
		const auto CaptureDef = DamageStatics().TagsToCaptureDefs[Pair.Value];

		float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key, false);
		
		float Resistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, Params, Resistance);
		Resistance = FMath::Clamp(Resistance, 0, 100.f);

		DamageTypeValue *= (100.f - Resistance) * 0.01f;
		Damage += DamageTypeValue;
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
		Damage *= FMath::Max(1.f, 1.f + SourceCriticalHitDamage * 0.01f - TargetCriticalHitResistance * 0.01f);
	}

	float TargetBlockChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, Params, TargetBlockChance);

	const bool bBlockedHit = FMath::RandRange(0.f, 100.f) <= TargetBlockChance;
	EffectContext->SetIsBlockHit(bBlockedHit);

	if (bBlockedHit) {
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
