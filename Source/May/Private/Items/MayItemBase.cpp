#include "Items/MayItemBase.h"

AMayItemBase::AMayItemBase() {
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AMayItemBase::BeginPlay() {
	Super::BeginPlay();
}

