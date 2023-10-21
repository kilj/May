// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UCombatActorInterface : public UInterface {
	GENERATED_BODY()
};

/**
 * This should be implemented by any actor, which can take part in any combat activities: casting, melee fight, etc
 */
class MAY_API ICombatActorInterface {
	GENERATED_BODY()

public:
	virtual FVector GetProjectileSpawnPosition() = 0;
};
