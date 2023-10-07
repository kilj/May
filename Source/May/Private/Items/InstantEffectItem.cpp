#include "Items/InstantEffectItem.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

AInstantEffectItem::AInstantEffectItem() {
}

void AInstantEffectItem::BeginPlay() {
	Super::BeginPlay();
}

void AInstantEffectItem::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass) {
	const auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;

	check(GameplayEffectClass);
	
	FGameplayEffectContextHandle EffectContext = TargetASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle EffectSpec = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.f, EffectContext);
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());
}
