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

	if (InstantApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);

	if (DurationApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap)
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);

	if (InfiniteApplicationPolicy == EEffectApplicationPolicy::ApplyOnBeginOverlap) {
		const auto ActiveEffectHandle = ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);

		if (ActiveEffectHandle.IsValid() && InfiniteRemovalPolicy != EEffectRemovalPolicy::DoNotRemove)
			ActiveEffectHandles.Add(ActiveEffectHandle, UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
	}
}

void AEffectItem::OnEndOverlap(AActor* TargetActor) {
	Super::OnEndOverlap(TargetActor);

	if (InstantApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);

	if (DurationApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);

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
