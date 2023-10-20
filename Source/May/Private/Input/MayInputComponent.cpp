// Red Beat, 2023

#include "Input/MayInputComponent.h"

UMayInputComponent::UMayInputComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


void UMayInputComponent::BeginPlay() {
	Super::BeginPlay();
}


void UMayInputComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}