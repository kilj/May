#include "AbilitySystem/MayAbilitySystemComponent.h"

#include "Utils/MayLogChannels.h"

void UMayAbilitySystemComponent::OnAbilityActorInfoSet() {
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UMayAbilitySystemComponent::EffectApplied);
}

void UMayAbilitySystemComponent::AddStartupAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities) {
	for (const auto AbilityClass : Abilities) {
		/*const */auto Spec = FGameplayAbilitySpec(AbilityClass, 1);
		//GiveAbility(Spec);
		GiveAbilityAndActivateOnce(Spec);
	}
}

void UMayAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle GEHandle) {
	FGameplayTagContainer TagsContainer;
	GESpec.GetAllAssetTags(TagsContainer);
	
	EffectAssetTagsDelegate.Broadcast(TagsContainer);
}
