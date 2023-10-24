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
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Weapon")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	//TODO: do we need property for this or just can hardcode it?
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Weapon")
	FName WeaponTipSocketName = FName();
	
	virtual void InitAbilityActorInfo();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Attributes")
	TSubclassOf<UGameplayEffect> DefaultVitalAttributes;

	void InitDefaultAttributes(TSubclassOf<UGameplayEffect> AttributesEffectClass, float Level = 1.0f);

	void AddStartupAbilities();

	//ICombatActorInterface
	virtual FVector GetProjectileSpawnLocation() override;
	//end of ICombatActorInterface

private:
	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
};
