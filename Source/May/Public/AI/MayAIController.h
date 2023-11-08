// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MayAIController.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class MAY_API AMayAIController : public AAIController {
	GENERATED_BODY()

public:
	AMayAIController();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;

};
