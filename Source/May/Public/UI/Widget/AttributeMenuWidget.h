// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "MayWidget.h"
#include "AttributeMenuWidget.generated.h"

USTRUCT(BlueprintType)
struct FAttributeMenuWidgetData {
	GENERATED_BODY()

	FAttributeMenuWidgetData() {}
	FAttributeMenuWidgetData(UMayAbilitySystemComponent* ASC, UMayAttributeSet* AS) : AbilitySystemComponent(ASC), AttributeSet(AS) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMayAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMayAttributeSet> AttributeSet = nullptr;
};

/**
 * 
 */
UCLASS(Blueprintable)
class MAY_API UAttributeMenuWidget : public UMayWidget {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="May|Widget")
	void InitWidget(const FAttributeMenuWidgetData Data);

	UFUNCTION(BlueprintCallable, Category="May|Widget")
	FORCEINLINE FAttributeMenuWidgetData GetWidgetData() const { return WidgetData; };

private:
	UPROPERTY()
	FAttributeMenuWidgetData WidgetData;
};
