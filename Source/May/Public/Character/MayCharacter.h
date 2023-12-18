// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Character/Interfaces/CombatActorInterface.h"
#include "Character/Interfaces/LevelInterface.h"
#include "MayCharacter.generated.h"

class ULevelInfo;
class UCharacterConfig;
class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnExperienceChangedSignature, const float /*NewLevel*/, const int32 /*Delta*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelChangedSignature, const float /*NewLevel*/);

UCLASS(Abstract)
class MAY_API AMayCharacter : public ACharacter, public IAbilitySystemInterface, public ILevelInterface, public ICombatActorInterface {
	GENERATED_BODY()

public:
	AMayCharacter();

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
	virtual AMayCharacter* GetMayCharacter_Implementation() override;
	virtual void Server_Die() override;
	//end of ICombatActorInterface

	UPROPERTY(EditAnywhere, Category="Defaults")
	TObjectPtr<UCharacterConfig> CharacterConfig; //TODO: change TObjectPtr to soft ref

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Defaults")
	TObjectPtr<ULevelInfo> LevelInfo; //TODO: change TObjectPtr to soft ref
	
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_Die();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Weapon")
	TObjectPtr<USkeletalMeshComponent> Weapon; //TODO: rename to current or equipped weapon?

	FOnExperienceChangedSignature OnExperienceChangedDelegate;
	FOnLevelChangedSignature OnLevelChangedDelegate;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	virtual void InitAbilityActorInfo();

	bool bDead = false;
	
	UFUNCTION(Client, Reliable)
	void Client_OnExperienceChanged(const float NewLevel, const int32 ExperienceDelta);
	
	UFUNCTION(Client, Reliable)
	void Client_OnLevelChanged(const float NewLevel);

private:
	UPROPERTY(EditAnywhere, Category="CombatActor")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY()
	FVector FacingTarget = FVector::Zero();
};
