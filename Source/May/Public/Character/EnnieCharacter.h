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
	virtual float GetLevel() override;
	virtual void AddExperience_Implementation(const int32 Experience) override;
	//end of ILevelInterface

	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	void InitDefaultAttributes(TSubclassOf<UGameplayEffect> AttributesEffectClass, float Level = 1.0f);

	void AddStartupAbilities();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	virtual void InitAbilityActorInfo() override;

};
