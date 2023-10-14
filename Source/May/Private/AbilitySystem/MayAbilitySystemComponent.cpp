#include "AbilitySystem/MayAbilitySystemComponent.h"

#include "Utils/MayLogChannels.h"

void UMayAbilitySystemComponent::OnAbilityActorInfoSet() {
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UMayAbilitySystemComponent::EffectApplied);
}

void UMayAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle GEHandle) {
	FGameplayTagContainer TagsContainer;
	GESpec.GetAllAssetTags(TagsContainer);
	
	EffectAssetTagsDelegate.Broadcast(TagsContainer);
}
