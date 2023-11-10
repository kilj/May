// Red Beat, 2023


#include "AI/Services/BTService_FindNearestPlayer.h"

#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void UBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const APawn* OwningPawn = AIOwner->GetPawn();
	const FName TargetTag = OwningPawn->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TargetTag, OutActors); //that's slow operation, maybe we should replace it with array of actors on GameState OR we can use normal gameplay tags and fire events

	AActor* NearestActor = nullptr;
	float NearestDistance = TNumericLimits<float>::Max();
	for (const auto Actor : OutActors) {
		const float Distance = OwningPawn->GetDistanceTo(Actor);
		if (Distance < NearestDistance) {
			NearestActor = Actor;
			NearestDistance = Distance;
		}
	}

	UBTFunctionLibrary::SetBlackboardValueAsObject(this, TargetToFollowSelector, NearestActor);
	UBTFunctionLibrary::SetBlackboardValueAsFloat(this, DistanceToTargetSelector, NearestDistance);
}
