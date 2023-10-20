#include "Player/EnniePlayerController.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayTagContainer.h"
#include "Core/Interfaces/HighlightInterface.h"
#include "Input/MayInputComponent.h"
#include "Utils/MayLogChannels.h"

AEnniePlayerController::AEnniePlayerController() {
	bReplicates = true;
}

void AEnniePlayerController::BeginPlay() {
	Super::BeginPlay();
	
	check(DefaultMappingContext);
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AEnniePlayerController::OnIAMove(const FInputActionValue& Value) {
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	const FRotator YawRotation = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>()) {
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AEnniePlayerController::OnAbilityInputTagPressed(FGameplayTag Tag) {
}

void AEnniePlayerController::OnAbilityInputTagReleased(FGameplayTag Tag) {
}

void AEnniePlayerController::OnAbilityInputTagHeld(FGameplayTag Tag) {
}

void AEnniePlayerController::CursorTrace() {
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if (Hit.bBlockingHit) {
		LastFrameHighlightedActor = ThisFrameHighlightedActor;
		ThisFrameHighlightedActor = Cast<IHighlightInterface>(Hit.GetActor());

		if (ThisFrameHighlightedActor != LastFrameHighlightedActor) {
			if (ThisFrameHighlightedActor)
				ThisFrameHighlightedActor->HighlightActor();

			if (LastFrameHighlightedActor)
				LastFrameHighlightedActor->UnHighlightActor();
		}
	}
}

void AEnniePlayerController::PlayerTick(float DeltaTime) {
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AEnniePlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	if (UMayInputComponent* MayInputComponent = CastChecked<UMayInputComponent>(InputComponent)) {
		MayInputComponent->BindAction(IAMove, ETriggerEvent::Triggered, this, &ThisClass::OnIAMove);
		
		MayInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::OnAbilityInputTagPressed, &ThisClass::OnAbilityInputTagReleased, &ThisClass::OnAbilityInputTagHeld);
	}
}
