// Red Beat, 2023

#include "UI/Components/DamageTextComponent.h"

UDamageTextComponent::UDamageTextComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UDamageTextComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDamageTextComponent::BeginPlay() {
	Super::BeginPlay();
}
