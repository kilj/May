// Red Beat, 2023

#include "Character/MayCharacter.h"
#include "AbilitySystemComponent.h"
#include "May.h"
#include "Components/CapsuleComponent.h"
#include "Utils/MayLogChannels.h"

AMayCharacter::AMayCharacter() {
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Ignore);

	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetMesh()->SetGenerateOverlapEvents(false);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AMayCharacter::GetAbilitySystemComponent() const {
	return AbilitySystemComponent;
}

UCharacterConfig* AMayCharacter::GetCharacterConfig_Implementation() const {
	return CharacterConfig.Get();
}

UAnimMontage* AMayCharacter::GetHitReactMontage_Implementation() const {
	return HitReactMontage;
}

void AMayCharacter::SetFacingTarget_Implementation(const FVector& Target) {
	FacingTarget = Target;
}

FVector AMayCharacter::GetFacingTarget_Implementation() const {
	return FacingTarget;
}

bool AMayCharacter::IsDead_Implementation() const {
	return bDead;
}

AMayCharacter* AMayCharacter::GetMayCharacter_Implementation() {
	return this;
}

void AMayCharacter::Server_Die() {
	GetAbilitySystemComponent()->ClearAllAbilities(); //for now, we'll remove all abilities on death to prevent using anything on dead character, but in future probably TODO: add bCanActivateWhenDead to ability?
	
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	Multicast_Die();
}

void AMayCharacter::Multicast_Die_Implementation() {
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	bDead = true;
}

void AMayCharacter::BeginPlay() {
	Super::BeginPlay();
}

void AMayCharacter::InitAbilityActorInfo() {
}

void AMayCharacter::Client_OnLevelChanged_Implementation(const float NewLevel) {
	MAY_ULOGW(this, TEXT("Called OnLevel changed: %f"), NewLevel);
	OnLevelChangedDelegate.Broadcast(NewLevel);

	OnLevelChanged(NewLevel); //event for UI
}

void AMayCharacter::Client_OnExperienceChanged_Implementation(const float NewLevel, const int32 ExperienceDelta) {
	MAY_ULOGW(this, TEXT("Called OnExperience changed: %f : +%i"), NewLevel, ExperienceDelta);
	OnExperienceChangedDelegate.Broadcast(NewLevel, ExperienceDelta);
}
