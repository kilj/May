// Red Beat, 2023

#include "AbilitySystem/MayAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/MayGameplayAbility.h"
#include "Utils/MayLogChannels.h"

void UMayAbilitySystemComponent::OnAbilityActorInfoSet() {
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &ThisClass::ClientEffectApplied);
}

void UMayAbilitySystemComponent::AddStartupAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities) {
	for (const auto AbilityClass : Abilities) {
		auto Spec = FGameplayAbilitySpec(AbilityClass, 1);

		if (const auto MayAbility = Cast<UMayGameplayAbility>(Spec.Ability)) {
			Spec.DynamicAbilityTags.AddTag(MayAbility->StartupInputTag);
		}

		GiveAbility(Spec);
	}
}

void UMayAbilitySystemComponent::OnAbilityInputTagPressed(FGameplayTag& Tag) {
}

void UMayAbilitySystemComponent::OnAbilityInputTagHeld(FGameplayTag& Tag) {
	if (!Tag.IsValid()) return;

	for (auto Spec : GetActivatableAbilities()) {
		AbilitySpecInputPressed(Spec);
		if (Spec.DynamicAbilityTags.HasTagExact(Tag) && !Spec.IsActive())
			TryActivateAbility(Spec.Handle);
	}
}

void UMayAbilitySystemComponent::OnAbilityInputTagReleased(FGameplayTag& Tag) {
	if (!Tag.IsValid()) return;
	
	for (auto Spec : GetActivatableAbilities()) {
		AbilitySpecInputReleased(Spec);
		//end ability for some abilities?
	}
}

void UMayAbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) {
	Super::OnGiveAbility(AbilitySpec);
	
	AbilityGivenDelegate.Broadcast(AbilitySpec);
}

void UMayAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle GEHandle) {
	FGameplayTagContainer TagsContainer;
	GESpec.GetAllAssetTags(TagsContainer);
	
	EffectAssetTagsDelegate.Broadcast(TagsContainer);
}
