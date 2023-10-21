#include "Character/MayCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/MayAbilitySystemComponent.h"
#include "Utils/MayLogChannels.h"

AMayCharacterBase::AMayCharacterBase() {
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AMayCharacterBase::GetAbilitySystemComponent() const {
	return AbilitySystemComponent;
}

FVector AMayCharacterBase::GetProjectileSpawnPosition() {
	return Weapon->GetSocketLocation(WeaponTipSocketName);
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
