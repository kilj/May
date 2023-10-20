#include "AbilitySystem/MayAbilitySystemComponent.h"

#include "AbilitySystem/Abilities/MayGameplayAbility.h"

void UMayAbilitySystemComponent::OnAbilityActorInfoSet() {
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UMayAbilitySystemComponent::EffectApplied);
}

void UMayAbilitySystemComponent::AddStartupAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities) {
	for (const auto AbilityClass : Abilities) {
		auto Spec = FGameplayAbilitySpec(AbilityClass, 1);

		if (const auto MayAbility = Cast<UMayGameplayAbility>(Spec.Ability)) {
			Spec.DynamicAbilityTags.AddTag(MayAbility->StartupInputTag);
		}

		GiveAbility(Spec);
		//GiveAbilityAndActivateOnce(Spec);
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

void UMayAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle GEHandle) {
	FGameplayTagContainer TagsContainer;
	GESpec.GetAllAssetTags(TagsContainer);
	
	EffectAssetTagsDelegate.Broadcast(TagsContainer);
}
