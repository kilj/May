// Red Beat, 2023

#include "Core/MayAssetManager.h"
#include "AbilitySystem/MayGameplayTags.h"

const UMayAssetManager& UMayAssetManager::Get() {
	check (GEngine->AssetManager);
	
	return *Cast<UMayAssetManager>(GEngine->AssetManager);
}

void UMayAssetManager::StartInitialLoading() {
	Super::StartInitialLoading();

	FMayGameplayTags::InitNativeGameplayTags();
}
