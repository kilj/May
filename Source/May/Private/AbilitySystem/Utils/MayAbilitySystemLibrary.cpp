// Red Beat, 2023

#include "AbilitySystem/Utils/MayAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/MayAbilityTypes.h"
#include "Core/MayGameMode.h"
#include "Kismet/GameplayStatics.h"

// UOverlayWidgetController* UMayAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject) {
// 	if (const auto PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0)) {
// 		if (const auto MayHUD = Cast<AMayHUD>(PC->GetHUD())) {
// 			const auto PS = PC->GetPlayerState<AEnniePlayerState>();
// 			const auto ASC = PS->GetAbilitySystemComponent();
// 			const auto AS = PS->GetAttributeSet();
//
// 			const FWidgetControllerParams Params (PC, PS, ASC, AS);
// 			return MayHUD->GetOverlayWidgetController(Params);
// 		}
// 	}
//
// 	return nullptr;
// }
//
// UAttributeWindowWidgetController* UMayAbilitySystemLibrary::GetAttributeWindowWidgetController(const UObject* WorldContextObject) {
// 	if (const auto PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0)) {
// 		if (const auto MayHUD = Cast<AMayHUD>(PC->GetHUD())) {
// 			const auto PS = PC->GetPlayerState<AEnniePlayerState>();
// 			const auto ASC = PS->GetAbilitySystemComponent();
// 			const auto AS = PS->GetAttributeSet();
//
// 			const FWidgetControllerParams Params (PC, PS, ASC, AS);
// 			return MayHUD->GetAttributeWindowWidgetController(Params);
// 		}
// 	}
//
// 	return nullptr;
// }

void UMayAbilitySystemLibrary::InitEnemyDefaultAttributes(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, EEnemyType EnemyType, int32 Level) {
	const auto MayGameMode = Cast<AMayGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (MayGameMode == nullptr) //TODO: game mode is nullptr on client, so we just skip this (applied GEs will be replicated from server anyways)
		return;
	
	const auto ETDefaultInfo = MayGameMode->EnemyTypesInfo->GetEnemyTypeDefaultInfo(EnemyType);

	FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
	EffectContext.AddSourceObject(ASC->GetAvatarActor());

	ASC->ApplyGameplayEffectSpecToSelf(*ASC->MakeOutgoingSpec(ETDefaultInfo.PrimaryAttributes, Level, EffectContext).Data.Get());
	ASC->ApplyGameplayEffectSpecToSelf(*ASC->MakeOutgoingSpec(ETDefaultInfo.SecondaryAttributes, Level, EffectContext).Data.Get());
	ASC->ApplyGameplayEffectSpecToSelf(*ASC->MakeOutgoingSpec(ETDefaultInfo.VitalAttributes, Level, EffectContext).Data.Get());
}

void UMayAbilitySystemLibrary::InitEnemyDefaultAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC) {
	const auto MayGameMode = Cast<AMayGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (MayGameMode == nullptr) //TODO: game mode is nullptr on client, so we just skip this (applied GEs will be replicated from server anyways)
		return;

	for (const auto AbilityClass : MayGameMode->EnemyTypesInfo->CommonAbilities) {
		ASC->GiveAbility(FGameplayAbilitySpec(AbilityClass, 1));
	}
	
}

bool UMayAbilitySystemLibrary::GetIsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle) {
	const auto EffectContext = static_cast<const FMayGameplayEffectContext*>(EffectContextHandle.Get()); //that c/c++ casting options are pretty shitty shit
	return EffectContext != nullptr ? EffectContext->IsBlockHit() : false;
}

bool UMayAbilitySystemLibrary::GetIsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle) {
	const auto EffectContext = static_cast<const FMayGameplayEffectContext*>(EffectContextHandle.Get()); //that c/c++ casting options are pretty shitty shit
	return EffectContext != nullptr ? EffectContext->IsCriticalHit() : false;
}

void UMayAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, const bool InValue) {
	if (const auto EffectContext = static_cast<FMayGameplayEffectContext*>(EffectContextHandle.Get()))
		EffectContext->SetIsBlockHit(InValue);
}

void UMayAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, const bool InValue) {
	if (const auto EffectContext = static_cast<FMayGameplayEffectContext*>(EffectContextHandle.Get()))
		EffectContext->SetIsCriticalHit(InValue);
}
