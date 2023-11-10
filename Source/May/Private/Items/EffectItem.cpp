// Red Beat, 2023

#include "Items/EffectItem.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AEffectItem::AEffectItem() {
}

void AEffectItem::BeginPlay() {
	Super::BeginPlay();
}

void AEffectItem::OnBeginOverlap(AActor* TargetActor) {
	Super::OnBeginOverlap(TargetActor);

	const bool bIsEnemy = TargetActor->ActorHasTag(FName("Enemy"));
	const bool bNeedApply = !bIsEnemy || (bIsEnemy && bApplyEffectToEnemies);

	if (bNeedApply && InstantApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap) {
		for (const auto Effect : InstantGameplayEffectClass)
			ApplyEffectToTarget(TargetActor, Effect);

		if (bDestroyOnEffectApplied)
			Destroy();
	}

	if (bNeedApply && DurationApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap) {
		for (const auto Effect : DurationGameplayEffectClass)
			ApplyEffectToTarget(TargetActor, Effect);

		if (bDestroyOnEffectApplied)
			Destroy();
	}

	if (bNeedApply && InfiniteApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap) {
		for (const auto Effect : InfiniteGameplayEffectClass) {
			const auto ActiveEffectHandle = ApplyEffectToTarget(TargetActor, Effect);

			if (ActiveEffectHandle.IsValid() && InfiniteRemovalPolicy != EEffectRemovalPolicy::DoNotRemove)
				ActiveEffectHandles.Add(ActiveEffectHandle, UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
		}

		if (bDestroyOnEffectApplied)
			Destroy();
	}
}

void AEffectItem::OnEndOverlap(AActor* TargetActor) {
	Super::OnEndOverlap(TargetActor);

	const bool bIsEnemy = TargetActor->ActorHasTag(FName("Enemy"));
	const bool bNeedApply = !bIsEnemy || (bIsEnemy && bApplyEffectToEnemies);

	if (bNeedApply && InstantApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap) {
		for (const auto Effect : InstantGameplayEffectClass)
			ApplyEffectToTarget(TargetActor, Effect);

		if (bDestroyOnEffectApplied)
			Destroy();
	}

	if (bNeedApply && DurationApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap) {
		for (const auto Effect : DurationGameplayEffectClass)
			ApplyEffectToTarget(TargetActor, Effect);

		if (bDestroyOnEffectApplied)
			Destroy();
	}

	if (InfiniteRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap) {
		const auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (IsValid(TargetASC)) {
			TArray<FActiveGameplayEffectHandle> ToRemove;
			for (auto Pair : ActiveEffectHandles) {
				if (TargetASC == Pair.Value) {
					TargetASC->RemoveActiveGameplayEffect(Pair.Key, 1);
					ToRemove.Add(Pair.Key);
				}
			}

			for (auto& Handle : ToRemove) {
				ActiveEffectHandles.FindAndRemoveChecked(Handle);
			}
		}
	}
}
