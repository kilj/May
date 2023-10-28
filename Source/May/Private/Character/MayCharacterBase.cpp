#include "Character/MayCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "May.h"
#include "AbilitySystem/MayAbilitySystemComponent.h"
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

FVector AMayCharacterBase::GetProjectileSpawnLocation() {
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

UAnimMontage* AMayCharacterBase::GetHitReactMontage_Implementation() {
	return HitReactMontage;
}

void AMayCharacterBase::Die() {
	//server
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandleDeath();
}

void AMayCharacterBase::MulticastHandleDeath_Implementation() {
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMayCharacterBase::BeginPlay() {
	Super::BeginPlay();
}

void AMayCharacterBase::InitAbilityActorInfo() {
}

void AMayCharacterBase::InitDefaultAttributes(const TSubclassOf<UGameplayEffect> AttributesEffectClass, const float Level) {
	if (AttributesEffectClass == nullptr) {
		MAY_ULOGERROR(TEXT("Can't init default attributes, because Attribute TSubclasOf is null"));
		return;
	}
	
	const auto ASC = GetAbilitySystemComponent();
	check(ASC);
	
	auto EffectContext = ASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const auto Spec = ASC->MakeOutgoingSpec(AttributesEffectClass, Level, EffectContext);
	ASC->ApplyGameplayEffectSpecToTarget(*Spec.Data.Get(), ASC);
}

void AMayCharacterBase::AddStartupAbilities() {
	if (!HasAuthority()) {
		MAY_ULOGWARNING(TEXT("Calling AMayCharacterBase::AddStartupAbilities from client!"));
		return;
	}

	const auto ASC = CastChecked<UMayAbilitySystemComponent>(AbilitySystemComponent);
	ASC->AddStartupAbilities(StartupAbilities);
	
}
