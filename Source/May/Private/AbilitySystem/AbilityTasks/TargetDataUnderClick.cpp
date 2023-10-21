// Red Beat, 2023


#include "AbilitySystem/AbilityTasks/TargetDataUnderClick.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/PlayerController.h"

UTargetDataUnderClick* UTargetDataUnderClick::CreateTargetDataUnderClick(UGameplayAbility* OwningAbility) {
	auto Obj = NewAbilityTask<UTargetDataUnderClick>(OwningAbility);
	
	
	return Obj;
}

void UTargetDataUnderClick::Activate() {
	const bool IsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (IsLocallyControlled) {
		//sending from client
		SendClickData();
	}
	else {
		//receiving on server
		const auto SpecHandle = GetAbilitySpecHandle();
		const auto OriginalPredictionKey = GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, OriginalPredictionKey).AddUObject(this, &ThisClass::OnTargetDataReplicatedCallback);
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, OriginalPredictionKey);
		if (!bCalledDelegate)
			SetWaitingOnRemotePlayerData();
	}
}

void UTargetDataUnderClick::SendClickData() {
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());
	
	if (const auto PC = Ability->GetCurrentActorInfo()->PlayerController.Get()) {
		FHitResult Hit;
		PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		if (Hit.bBlockingHit) {
			FGameplayAbilityTargetDataHandle DataHandle;
			FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
			Data->HitResult = Hit;
			DataHandle.Add(Data);

			AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(), DataHandle, FGameplayTag(), AbilitySystemComponent->ScopedPredictionKey);

			if (ShouldBroadcastAbilityTaskDelegates())
				OnValidData.Broadcast(DataHandle);
		}
	}
}

void UTargetDataUnderClick::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag) {
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());

	if (ShouldBroadcastAbilityTaskDelegates())
		OnValidData.Broadcast(DataHandle);
}
