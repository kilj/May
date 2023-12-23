// Red Beat, 2023

#include "AbilitySystem/Utils/MayAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/MayAbilityTypes.h"
#include "Core/MayGameMode.h"
#include "Character/Interfaces/CombatActorInterface.h"
#include "Kismet/GameplayStatics.h"

void UMayAbilitySystemLibrary::InitEnemyDefaultAttributes(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, const EEnemyType EnemyType, const float Level) {
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

void UMayAbilitySystemLibrary::InitEnemyDefaultAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, const EEnemyType EnemyType, const float Level) {
	const auto MayGameMode = Cast<AMayGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (MayGameMode == nullptr) //TODO: game mode is nullptr on client, so we just skip this (applied GEs will be replicated from server anyways)
		return;

	for (const auto AbilityClass : MayGameMode->EnemyTypesInfo->CommonAbilities) {
		ASC->GiveAbility(FGameplayAbilitySpec(AbilityClass, FMath::FloorToInt(Level)));
	}

	for (const auto AbilityClass : MayGameMode->EnemyTypesInfo->GetEnemyTypeDefaultInfo(EnemyType).Abilities) {
		ASC->GiveAbility(FGameplayAbilitySpec(AbilityClass, FMath::FloorToInt(Level)));
	}
	
}

FEnemyTypeDefaultInfo UMayAbilitySystemLibrary::GetEnemyTypeInfo(const UObject* WorldContextObject, const EEnemyType EnemyType) {
	const auto MayGameMode = Cast<AMayGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (MayGameMode == nullptr)
		return FEnemyTypeDefaultInfo();
	
	return MayGameMode->EnemyTypesInfo->GetEnemyTypeDefaultInfo(EnemyType);
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

void UMayAbilitySystemLibrary::GetLivePlayersInRadius(const UObject* WorldContextObject, const FVector& FromOrigin, float Radius, TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, bool bDrawDebug) {
	FCollisionQueryParams SphereParams;
	SphereParams.MobilityType = EQueryMobilityType::Dynamic; //players have dynamic mobility type 
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	TArray<FOverlapResult> Overlaps;
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull)) {
		World->OverlapMultiByObjectType(Overlaps, FromOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);

		if (bDrawDebug)
			DrawDebugSphere(World, FromOrigin, Radius, 12, FColor::Green, false, 0.5f);

		for (auto OverlapResult : Overlaps) {
			const auto Actor = OverlapResult.GetActor();
			if (Actor->Implements<UCombatActorInterface>() && !ICombatActorInterface::Execute_IsDead(Actor))
				OutOverlappingActors.AddUnique(OverlapResult.GetActor());
		}
	}

}