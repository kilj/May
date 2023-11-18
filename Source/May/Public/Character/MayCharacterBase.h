// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Character/Interfaces/CombatActorInterface.h"
#include "Character/Interfaces/LevelInterface.h"
#include "MayCharacterBase.generated.h"

class UCharacterConfig;
class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class MAY_API AMayCharacterBase : public ACharacter, public IAbilitySystemInterface, public ILevelInterface, public ICombatActorInterface {
	GENERATED_BODY()

public:
	AMayCharacterBase();

	UFUNCTION(BlueprintCallable)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	//ICombatActorInterface
	virtual UCharacterConfig* GetCharacterConfig_Implementation() const override;
	virtual UAnimMontage* GetHitReactMontage_Implementation() const override;
	virtual void SetFacingTarget_Implementation(const FVector& Target) override;
	virtual FVector GetFacingTarget_Implementation() const override;
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation() override;
	virtual void Server_Die() override;
	//end of ICombatActorInterface

	UPROPERTY(EditAnywhere, Category="Defaults")
	TObjectPtr<UCharacterConfig> CharacterConfig; //TODO: change TObjectPtr to soft ref
	
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_Die();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Weapon")
	TObjectPtr<USkeletalMeshComponent> Weapon; //TODO: rename to current or equipped weapon?
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void InitAbilityActorInfo();

	bool bDead = false;

private:
	UPROPERTY(EditAnywhere, Category="CombatActor")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY()
	FVector FacingTarget = FVector::Zero();
};
