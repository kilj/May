// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LevelInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class ULevelInterface : public UInterface {
	GENERATED_BODY()
};

/**
 * Interface, which should be used on the actors, who have level and use it in attribute calculations.
 * Ennie holds Level on its PlayerState.
 * Any enemy keeps Level on itself.
 *
 * Level calculations should always be server-only.
 */
class MAY_API ILevelInterface {
	GENERATED_BODY()

public:

	// Get character's level
	virtual float GetLevel();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddExperience(const int32 Experience);
};
