#include "Character/EnnieCharacter.h"

#include "AbilitySystem/MayAbilitySystemComponent.h"
#include "AbilitySystem/MayAttributeSet.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "GameFramework/PlayerState.h"
#include "Player/EnniePlayerController.h"
#include "Player/EnniePlayerState.h"
#include "UI/HUD/MayHUD.h"

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
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AEnnieCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
}

void AEnnieCharacter::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();	//server version
	InitAttributes(); //init default attributes on server, so they will be replicated to clients
}

void AEnnieCharacter::OnRep_PlayerState() {
	Super::OnRep_PlayerState();

	InitAbilityActorInfo(); //client version
}

void AEnnieCharacter::InitAbilityActorInfo() {
	Super::InitAbilityActorInfo();
	
	if (const auto PS = GetPlayerState<AEnniePlayerState>()) {
		AttributeSet = PS->GetAttributeSet();
		AbilitySystemComponent = PS->GetAbilitySystemComponent();
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);

		Cast<UMayAbilitySystemComponent>(AbilitySystemComponent)->OnAbilityActorInfoSet();

		// player controller will be null on non-locally controlled client
		if (const auto PC = Cast<AEnniePlayerController>(GetController())) {
			if (const auto HUD = Cast<AMayHUD>(PC->GetHUD())) {
				HUD->InitOverlay(PC, PS, AbilitySystemComponent, AttributeSet);
			}
		}
	}
}
