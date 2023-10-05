#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "EnniePlayerController.generated.h"

class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class IHighlightInterface;

UCLASS()
class AEnniePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AEnniePlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* IAMoveAction;

	virtual void PlayerTick(float DeltaTime) override;
protected:
	virtual void SetupInputComponent() override;
	
	virtual void BeginPlay() override;

private:
	void Move(const FInputActionValue& Value);

	void CursorTrace();

	IHighlightInterface* LastFrameHighlightedActor; 
	IHighlightInterface* ThisFrameHighlightedActor; 
};


