// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "EnniePlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 
 */
UCLASS()
class MAY_API AEnniePlayerState : public APlayerState, public IAbilitySystemInterface {
	GENERATED_BODY()

public:
	AEnniePlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	FORCEINLINE float GetPlayerLevel() const { return Level; }
	FORCEINLINE void SetPlayerLevel(const float NewLevel) { Level = NewLevel; }

	UPROPERTY(VisibleAnywhere, Replicated)
	int32 AttributePoints = 0; //TODO: this should be used only on server

	UPROPERTY(VisibleAnywhere, Replicated)
	int32 SpellPoints = 0; //TODO: this should be used only on server
	
protected:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	float Level = 1.f;

	UFUNCTION()
	void OnRep_Level(float OldLevel);
};
