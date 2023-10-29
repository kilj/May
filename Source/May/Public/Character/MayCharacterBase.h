#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Core/Interfaces/CombatActorInterface.h"
#include "Core/Interfaces/LevelInterface.h"
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

	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath(); //TODO: rename to Multicast_Die()?
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Weapon")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	virtual void InitAbilityActorInfo();

	//TODO: Move to EnnieCharacter because of we initing attributes for enemy from enemytypeinfo (gamemode)
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	//TODO: Move to EnnieCharacter because of we initing attributes for enemy from enemytypeinfo (gamemode)
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	//TODO: Move to EnnieCharacter because of we initing attributes for enemy from enemytypeinfo (gamemode)
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	//TODO: Move to EnnieCharacter because of we initing attributes for enemy from enemytypeinfo (gamemode)
	void InitDefaultAttributes(TSubclassOf<UGameplayEffect> AttributesEffectClass, float Level = 1.0f);

	void AddStartupAbilities();

	//ICombatActorInterface
	virtual FVector GetProjectileSpawnLocation() override;
	virtual UAnimMontage* GetHitReactMontage_Implementation() override;
	virtual void Die() override; //TODO: rename to Server_Die() ?
	//end of ICombatActorInterface

private:
	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;

	//TODO: do we need property for this or just can hardcode it?
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="CombatActor", meta=(AllowPrivateAccess="true"))
	FName WeaponTipSocketName = FName();

	UPROPERTY(EditAnywhere, Category="CombatActor")
	TObjectPtr<UAnimMontage> HitReactMontage;
};
