// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MayGameMode.generated.h"

class UEnemyTypeInfo;
class UAttributeInfo;

UCLASS(minimalapi)
class AMayGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMayGameMode();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributesInfo;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UEnemyTypeInfo> EnemyTypesInfo;
};



