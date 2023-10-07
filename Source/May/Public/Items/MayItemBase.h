#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MayItemBase.generated.h"

class USphereComponent;

UCLASS()
class MAY_API AMayItemBase : public AActor {
	GENERATED_BODY()

public:
	AMayItemBase();

protected:
	virtual void BeginPlay() override;
};
