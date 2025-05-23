// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MayAbilitySystemComponent.generated.h"

class UMayGameplayAbility;

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAbilityGiven, const FGameplayAbilitySpec& /*AbilitySpec*/);

/**
 * Extended version of AbilitySystemComponent for May project
 */
UCLASS()
class MAY_API UMayAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityActorInfoSet();

	FEffectAssetTags EffectAssetTagsDelegate;
	FOnAbilityGiven AbilityGivenDelegate;

	void AddStartupAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities);

	void OnAbilityInputTagPressed(FGameplayTag& Tag);
	void OnAbilityInputTagHeld(FGameplayTag& Tag);
	void OnAbilityInputTagReleased(FGameplayTag& Tag);

protected:

	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle GEHandle);

	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	
};
