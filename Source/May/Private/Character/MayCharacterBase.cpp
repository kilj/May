// Red Beat, 2023

#include "Character/MayCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "May.h"
#include "Components/CapsuleComponent.h"
#include "Utils/MayLogChannels.h"

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

AMayCharacterBase* AMayCharacterBase::GetMayCharacter_Implementation() {
	return this;
}

void AMayCharacterBase::Server_Die() {
	GetAbilitySystemComponent()->ClearAllAbilities(); //for now, we'll remove all abilities on death to prevent using anything on dead character, but in future probably TODO: add bCanActivateWhenDead to ability?
	
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

void AMayCharacterBase::Client_OnLevelChanged_Implementation(const float NewLevel) {
	MAY_ULOGW(this, TEXT("Called OnLevel changed: %f"), NewLevel);
	OnLevelChangedDelegate.Broadcast(NewLevel);
}

void AMayCharacterBase::Client_OnExperienceChanged_Implementation(const float NewLevel, const int32 ExperienceDelta) {
	MAY_ULOGW(this, TEXT("Called OnExperience changed: %f | +%i"), NewLevel, ExperienceDelta);
	OnExperienceChangedDelegate.Broadcast(NewLevel, ExperienceDelta);
}
