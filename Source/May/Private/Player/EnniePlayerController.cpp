#include "Player/EnniePlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Pawn.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/MayAbilitySystemComponent.h"
#include "Core/Interfaces/HighlightInterface.h"
#include "GameFramework/Character.h"
#include "Input/MayInputComponent.h"
#include "UI/Components/DamageTextComponent.h"

AEnniePlayerController::AEnniePlayerController() {
	bReplicates = true;
}

UMayAbilitySystemComponent* AEnniePlayerController::GetASC() {
	if (AbilitySystemComponent == nullptr)
		AbilitySystemComponent = Cast<UMayAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));

	return AbilitySystemComponent;
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
	if (GetASC()) GetASC()->OnAbilityInputTagPressed(Tag);
}

void AEnniePlayerController::OnAbilityInputTagReleased(FGameplayTag Tag) {
	if (GetASC()) GetASC()->OnAbilityInputTagReleased(Tag);
}

void AEnniePlayerController::OnAbilityInputTagHeld(FGameplayTag Tag) {
	if (GetASC()) GetASC()->OnAbilityInputTagHeld(Tag);
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

void AEnniePlayerController::ShowReceivedDamage_Implementation(const float DamageAmount, ACharacter* TargetCharacter, FColor TextColor) {
	if (IsValid(TargetCharacter) && DamageTextComponentClass) {
		const auto DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->ShowDamageText(DamageAmount, TextColor);
	} 
}

void AEnniePlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	if (UMayInputComponent* MayInputComponent = CastChecked<UMayInputComponent>(InputComponent)) {
		MayInputComponent->BindAction(IAMove, ETriggerEvent::Triggered, this, &ThisClass::OnIAMove);
		
		MayInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::OnAbilityInputTagPressed, &ThisClass::OnAbilityInputTagReleased, &ThisClass::OnAbilityInputTagHeld);
	}
}
