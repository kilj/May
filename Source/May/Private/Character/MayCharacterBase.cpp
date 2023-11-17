// Red Beat, 2023

#include "Character/MayCharacterBase.h"
#include "May.h"
#include "Character/Data/CharacterConfig.h"
#include "Components/CapsuleComponent.h"

AMayCharacterBase::AMayCharacterBase() {
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Ignore);

	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetMesh()->SetGenerateOverlapEvents(false);

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AMayCharacterBase::GetAbilitySystemComponent() const {
	return AbilitySystemComponent;
}

UCharacterConfig* AMayCharacterBase::GetCharacterConfig_Implementation() const {
	return CharacterConfig.Get();
}

FVector AMayCharacterBase::GetWeaponTipLocation_Implementation() const {
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

UAnimMontage* AMayCharacterBase::GetHitReactMontage_Implementation() const {
	return HitReactMontage;
}

void AMayCharacterBase::SetFacingTarget_Implementation(const FVector& Target) {
	FacingTarget = Target;
}

FVector AMayCharacterBase::GetFacingTarget_Implementation() const {
	return FacingTarget;
}

bool AMayCharacterBase::IsDead_Implementation() const {
	return bDead;
}

AActor* AMayCharacterBase::GetAvatar_Implementation() {
	return this;
}

void AMayCharacterBase::Server_Die() {
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	Multicast_Die();
}

void AMayCharacterBase::Multicast_Die_Implementation() {
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

void AMayCharacterBase::BeginPlay() {
	Super::BeginPlay();
}

void AMayCharacterBase::InitAbilityActorInfo() {
}