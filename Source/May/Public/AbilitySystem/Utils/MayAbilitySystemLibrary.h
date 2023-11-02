// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/EnemyTypeInfo.h"
#include "MayAbilitySystemLibrary.generated.h"

struct FGameplayEffectContextHandle;
class UAbilitySystemComponent;
class UAttributeWindowWidgetController;
class UOverlayWidgetController;

/**
 * Blueprint function library for the May project.
 */
UCLASS()
class MAY_API UMayAbilitySystemLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

public:
	// UFUNCTION(BlueprintPure, Category="MayAbilitySystemLibrary|WidgetController")
	// static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	//
	// UFUNCTION(BlueprintPure, Category="MayAbilitySystemLibrary|WidgetController")
	// static UAttributeWindowWidgetController* GetAttributeWindowWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="MayAbilitySystemLibrary")
	static void InitEnemyDefaultAttributes(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, EEnemyType EnemyType, int32 Level);
	
	UFUNCTION(BlueprintCallable, Category="MayAbilitySystemLibrary")
	static void InitEnemyDefaultAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintPure, Category="MayAbilitySystemLibrary|GameplayEffects")
	static bool GetIsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="MayAbilitySystemLibrary|GameplayEffects")
	static bool GetIsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable, Category="MayAbilitySystemLibrary|GameplayEffects")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool InValue);
	
	UFUNCTION(BlueprintCallable, Category="MayAbilitySystemLibrary|GameplayEffects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool InValue);
	
};
