#include "Items/MayItemBase.h"

#include "Components/SphereComponent.h"
#include "Utils/MayLogChannels.h"

AMayItemBase::AMayItemBase() {
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AMayItemBase::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	MAY_ULOG(TEXT("Actor %s BEGIN overlap with %s"), *OtherActor->GetActorNameOrLabel(), *GetActorNameOrLabel());
}

void AMayItemBase::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	MAY_ULOG(TEXT("Actor %s END overlap with %s"), *OtherActor->GetActorNameOrLabel(), *GetActorNameOrLabel());
}

void AMayItemBase::BeginPlay() {
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AMayItemBase::OnBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AMayItemBase::OnEndOverlap);
}

