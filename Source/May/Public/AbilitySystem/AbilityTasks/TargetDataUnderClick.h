// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderClick.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FClickTargetDataSignature, const FGameplayAbilityTargetDataHandle&, DataHandle);

/**
 * 
 */
UCLASS()
class MAY_API UTargetDataUnderClick : public UAbilityTask
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (/*DisplayName="CreateTargetDataUnderClick", */HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UTargetDataUnderClick* CreateTargetDataUnderClick(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FClickTargetDataSignature OnValidData;

private:
	virtual void Activate() override;

	void SendClickData();

	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag);
};
