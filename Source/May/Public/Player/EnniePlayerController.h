#pragma once

#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "EnniePlayerController.generated.h"

class UDamageTextComponent;
struct FGameplayTag;
struct FInputActionValue;
class UMayInputConfig;
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
class IHighlightInterface;
class UMayAbilitySystemComponent;

UCLASS()
class AEnniePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AEnniePlayerController();

	UMayAbilitySystemComponent* GetASC();

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* IAMove;
	
	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION(Client, Unreliable)
	void ShowReceivedDamage(const float DamageAmount, ACharacter* TargetCharacter);
	
protected:
	virtual void SetupInputComponent() override;
	
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UMayAbilitySystemComponent> AbilitySystemComponent;

	void OnIAMove(const FInputActionValue& Value);

	void OnAbilityInputTagPressed(FGameplayTag Tag);
	void OnAbilityInputTagReleased(FGameplayTag Tag);
	void OnAbilityInputTagHeld(FGameplayTag Tag);

	void CursorTrace();

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UMayInputConfig> InputConfig;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextComponentClass;

	IHighlightInterface* LastFrameHighlightedActor; 
	IHighlightInterface* ThisFrameHighlightedActor;
};


