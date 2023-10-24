// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "MayWidget.h"
#include "StatusBarWidget.generated.h"

class UMayAbilitySystemComponent;
class UMayAttributeSet;
struct FGameplayAttribute;

USTRUCT(BlueprintType)
struct FStatusBarWidgetData {
	GENERATED_BODY()

public:
	FStatusBarWidgetData() {}
	FStatusBarWidgetData(UMayAbilitySystemComponent* ASC, UMayAttributeSet* AS) : AbilitySystemComponent(ASC), AttributeSet(AS) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMayAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMayAttributeSet> AttributeSet = nullptr;
};

/**
 * 
 */
UCLASS(Blueprintable)
class MAY_API UStatusBarWidget : public UMayWidget {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="May|Widget")
	void InitWidget(const FStatusBarWidgetData Data);

	UFUNCTION(BlueprintCallable, Category="May|Widget")
	FORCEINLINE FStatusBarWidgetData GetWidgetData() const { return WidgetData; };

private:
	UPROPERTY()
	FStatusBarWidgetData WidgetData;
};
