// Red Beat, 2023


#include "AI/Services/BTService_FindNearestPlayer.h"

#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const APawn* OwningPawn = AIOwner->GetPawn();
	const FName TargetTag = OwningPawn->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TargetTag, OutActors); //that's slow operation, maybe we should replace it with array of actors on GameState OR we can use normal gameplay tags and fire events

	AActor* NearestActor = nullptr;
	float Distance = TNumericLimits<float>::Max();
	for (auto Actor : OutActors) {
		if (OwningPawn->GetDistanceTo(Actor) < Distance)
			NearestActor = Actor;
	}

	if (NearestActor)
		GEngine->AddOnScreenDebugMessage(1, 0.5, FColor::Red, *FString::Printf(TEXT("Nearest actor: %s"), *NearestActor->GetActorNameOrLabel()));
	else
		GEngine->AddOnScreenDebugMessage(2, 0.5, FColor::Green, TEXT("Nearest actor is nullptr"));
}
