// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Character/Interfaces/CombatActorInterface.h"
#include "Character/Interfaces/LevelInterface.h"
#include "MayCharacterBase.generated.h"

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
	virtual FVector GetWeaponTipLocation_Implementation() const override;
	virtual UAnimMontage* GetHitReactMontage_Implementation() const override;
	virtual void SetFacingTarget_Implementation(const FVector& Target) override;
	virtual FVector GetFacingTarget_Implementation() const override;
	virtual bool IsDead_Implementation() const override;
	virtual AActor* GetAvatar_Implementation() override;
	virtual void Server_Die() override;
	//end of ICombatActorInterface
	
	UFUNCTION(NetMulticast, Reliable)
	virtual void Multicast_Die();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Weapon")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	virtual void InitAbilityActorInfo();

private:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="CombatActor", meta=(AllowPrivateAccess="true"))
	FName WeaponTipSocketName = FName();

	UPROPERTY(EditAnywhere, Category="CombatActor")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY()
	FVector FacingTarget = FVector::Zero();

	bool bDead = false;
};
