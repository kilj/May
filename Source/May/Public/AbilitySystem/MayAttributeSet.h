#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "MayAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties {
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceASC = nullptr;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetASC = nullptr;

	UPROPERTY()
	TObjectPtr<AActor> SourceAvatarActor = nullptr;

	UPROPERTY()
	TObjectPtr<AActor> TargetAvatarActor = nullptr;

	UPROPERTY()
	TObjectPtr<AController> SourceController = nullptr;

	UPROPERTY()
	TObjectPtr<AController> TargetController = nullptr;

	UPROPERTY()
	TObjectPtr<ACharacter> SourceCharacter = nullptr;

	UPROPERTY()
	TObjectPtr<ACharacter> TargetCharacter = nullptr;

	FGameplayEffectContextHandle EffectContextHandle;

	FEffectProperties(){}
};

/**
 * 
 */
UCLASS()
class MAY_API UMayAttributeSet : public UAttributeSet {
	GENERATED_BODY()

public:
	UMayAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Health, Category="Primary Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMayAttributeSet, Health);

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxHealth, Category="Primary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMayAttributeSet, MaxHealth);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Mana, Category="Primary Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UMayAttributeSet, Mana);
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxMana, Category="Primary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UMayAttributeSet, MaxMana);

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Properties);

	void ClampAttributeValues(const FGameplayAttribute& Attribute, float& NewValue) const;
	
};
