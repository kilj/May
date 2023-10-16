#include "Character/MayCharacterBase.h"
#include "AbilitySystemComponent.h"

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

void AMayCharacterBase::InitAbilityActorInfo() {
}

void AMayCharacterBase::InitDefaultAttributes(const TSubclassOf<UGameplayEffect> AttributesEffectClass, const float Level) const {
	check(AttributesEffectClass);
	
	const auto ASC = GetAbilitySystemComponent();
	check(ASC);
	
	auto EffectContext = ASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const auto Spec = ASC->MakeOutgoingSpec(AttributesEffectClass, Level, EffectContext);
	ASC->ApplyGameplayEffectSpecToTarget(*Spec.Data.Get(), ASC);
}
