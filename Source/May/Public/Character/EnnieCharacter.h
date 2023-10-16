// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "MayCharacterBase.h"
#include "EnnieCharacter.generated.h"

class UMayAbilitySystemComponent;
class UMayAttributeSet;

UCLASS(Blueprintable)
class AEnnieCharacter : public AMayCharacterBase {
	GENERATED_BODY()

public:
	AEnnieCharacter();

	//ILevelInterface
	virtual int32 GetLevel() override;
	//end of ILevelInterface

	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	virtual void InitAbilityActorInfo() override;

};
