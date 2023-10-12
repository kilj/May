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

	if (InstantApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap) {
		for (const auto Effect : InstantGameplayEffectClass)
			ApplyEffectToTarget(TargetActor, Effect);
	}

	if (DurationApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap) {
		for (const auto Effect : DurationGameplayEffectClass)
			ApplyEffectToTarget(TargetActor, Effect);
	}

	if (InfiniteApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap) {
		for (const auto Effect : InfiniteGameplayEffectClass) {
			const auto ActiveEffectHandle = ApplyEffectToTarget(TargetActor, Effect);

			if (ActiveEffectHandle.IsValid() && InfiniteRemovalPolicy != EEffectRemovalPolicy::DoNotRemove)
				ActiveEffectHandles.Add(ActiveEffectHandle, UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
		}
	}
}

void AEffectItem::OnEndOverlap(AActor* TargetActor) {
	Super::OnEndOverlap(TargetActor);

	if (InstantApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap) {
		for (const auto Effect : InstantGameplayEffectClass)
			ApplyEffectToTarget(TargetActor, Effect);
	}

	if (DurationApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap) {
		for (const auto Effect : DurationGameplayEffectClass)
			ApplyEffectToTarget(TargetActor, Effect);
	}

	if (InfiniteRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap) {
		const auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (IsValid(TargetASC)) {
			TArray<FActiveGameplayEffectHandle> ToRemove;
			for (auto KVP : ActiveEffectHandles) {
				if (TargetASC == KVP.Value) {
					TargetASC->RemoveActiveGameplayEffect(KVP.Key, 1);
					ToRemove.Add(KVP.Key);
				}
			}

			for (auto& Handle : ToRemove) {
				ActiveEffectHandles.FindAndRemoveChecked(Handle);
			}
		}
	}
}
