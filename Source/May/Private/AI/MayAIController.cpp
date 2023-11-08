// Red Beat, 2023

#include "AI/MayAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AMayAIController::AMayAIController() {
	PrimaryActorTick.bCanEverTick = true;

	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("Blackboard");
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComponent");
}

void AMayAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AMayAIController::BeginPlay() {
	Super::BeginPlay();
	
}
