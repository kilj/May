// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MayAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class MAY_API UMayAssetManager : public UAssetManager {
	GENERATED_BODY()

public:
	static const UMayAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
