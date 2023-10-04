#include "Character/MayCharacterBase.h"

AMayCharacterBase::AMayCharacterBase() {
	PrimaryActorTick.bCanEverTick = false;

	// WeaponSocket = CreateDefaultSubobject<USceneComponent>(FName("WeaponSocket"));
	// WeaponSocket->SetupAttachment(GetMesh()/*, FName("")*/);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AMayCharacterBase::GetAbilitySystemComponent() const {
	return AbilitySystemComponent;
}

void AMayCharacterBase::BeginPlay() {
	Super::BeginPlay();
}
