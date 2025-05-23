// Red Beat, 2023

#include "Character/EnnieCharacter.h"
#include "AbilitySystem/MayAbilitySystemComponent.h"
#include "AbilitySystem/MayAttributeSet.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Character/Data/LevelInfo.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/EnniePlayerController.h"
#include "Player/EnniePlayerState.h"
#include "UI/HUD/MayHUD.h"
#include "Utils/MayLogChannels.h"

AEnnieCharacter::AEnnieCharacter() {
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

float AEnnieCharacter::GetLevel() {
	if (const auto PS = GetPlayerState<AEnniePlayerState>())
		return PS->GetPlayerLevel();

	return 1.f;
}

void AEnnieCharacter::AddExperience_Implementation(const int32 Experience) {
	//TODO: check Exp > 0
	
	const auto PS = GetPlayerState<AEnniePlayerState>();
	check(PS);

	if (LevelInfo == nullptr) {
		MAY_ULOGE(this, TEXT("Can't add experience to %s, because LevelInfo data asset is null for this character"), *GetActorNameOrLabel());
		return;
	}

	const auto OldLevel = PS->GetPlayerLevel();
	const auto OldExperience = LevelInfo->GetExperience(OldLevel);

	const auto NewExperience = OldExperience + Experience;
	const auto NewLevel = LevelInfo->GetLevel(NewExperience);
	
	for (int i = FMath::FloorToInt(OldLevel) + 1; i <= FMath::FloorToInt(NewLevel); ++i) {
		MAY_ULOGW(this, TEXT("%s got level %i!"), *GetActorNameOrLabel(), i);
		Multicast_OnLevelChanged(i);

		//TODO: grant here levelup bonuses - attribute points, etc
	}

	Client_OnExperienceChanged(NewLevel, Experience);
	
	PS->SetPlayerLevel(NewLevel);
}

void AEnnieCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
}

//server version
void AEnnieCharacter::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();	
	InitDefaultAttributes(DefaultPrimaryAttributes); //init default primary attributes on server, so they will be replicated to clients...
	InitDefaultAttributes(DefaultSecondaryAttributes); //... and do the same with secondary attributes
	InitDefaultAttributes(DefaultVitalAttributes); //... in the end we should set initial values for Health/Mana

	AddStartupAbilities();
}

//client version
void AEnnieCharacter::OnRep_PlayerState() {
	Super::OnRep_PlayerState();

	InitAbilityActorInfo(); 
}

void AEnnieCharacter::InitDefaultAttributes(const TSubclassOf<UGameplayEffect> AttributesEffectClass, const float Level) {
	if (AttributesEffectClass == nullptr) {
		MAY_ULOGE(this, TEXT("Can't init default attributes, because Attribute TSubclasOf is null"));
		return;
	}
	
	const auto ASC = GetAbilitySystemComponent();
	if (ASC == nullptr) return;
	
	auto EffectContext = ASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const auto Spec = ASC->MakeOutgoingSpec(AttributesEffectClass, Level, EffectContext);
	ASC->ApplyGameplayEffectSpecToTarget(*Spec.Data.Get(), ASC);
}

void AEnnieCharacter::AddStartupAbilities() {
	if (!HasAuthority()) {
		MAY_ULOGW(this, TEXT("Calling AEnnieCharacter::AddStartupAbilities from client!"));
		return;
	}

	const auto ASC = Cast<UMayAbilitySystemComponent>(AbilitySystemComponent);
	if (ASC)
		ASC->AddStartupAbilities(StartupAbilities);
}

void AEnnieCharacter::InitAbilityActorInfo() {
	Super::InitAbilityActorInfo();
	
	if (const auto PS = GetPlayerState<AEnniePlayerState>()) {
		AttributeSet = PS->GetAttributeSet();
		AbilitySystemComponent = PS->GetAbilitySystemComponent();
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);

		Cast<UMayAbilitySystemComponent>(AbilitySystemComponent)->OnAbilityActorInfoSet();

		// player controller will be null on non-locally controlled client TODO: move it in some early client method
		if (const auto PC = Cast<AEnniePlayerController>(GetController())) {
			if (const auto HUD = Cast<AMayHUD>(PC->GetHUD())) {
				HUD->InitOverlay(AbilitySystemComponent, AttributeSet, this);
			}
		}
	}
}
