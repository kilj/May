#include "..\..\Public\Player\EnniePlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Core/Interfaces/HighlightInterface.h"

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

void AEnniePlayerController::Move(const FInputActionValue& Value) {
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	const FRotator YawRotation = FRotator(0.0f, GetControlRotation().Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>()) {
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
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

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) {
		EnhancedInputComponent->BindAction(IAMoveAction, ETriggerEvent::Triggered, this, &AEnniePlayerController::Move);
	}
}
