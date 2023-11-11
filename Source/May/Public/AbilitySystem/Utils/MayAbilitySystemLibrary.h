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
	UFUNCTION(BlueprintCallable, Category="MayAbilitySystemLibrary")
	static void InitEnemyDefaultAttributes(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, const EEnemyType EnemyType, const int32 Level);
	
	UFUNCTION(BlueprintCallable, Category="MayAbilitySystemLibrary")
	static void InitEnemyDefaultAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, const EEnemyType EnemyType, const int32 Level);

	UFUNCTION(BlueprintCallable, Category="MayAbilitySystemLibrary")
	static FEnemyTypeDefaultInfo GetEnemyTypeInfo(const UObject* WorldContextObject, const EEnemyType EnemyType);

	UFUNCTION(BlueprintPure, Category="MayAbilitySystemLibrary|GameplayEffects")
	static bool GetIsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="MayAbilitySystemLibrary|GameplayEffects")
	static bool GetIsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable, Category="MayAbilitySystemLibrary|GameplayEffects")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool InValue);
	
	UFUNCTION(BlueprintCallable, Category="MayAbilitySystemLibrary|GameplayEffects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle, bool InValue);
	
};
