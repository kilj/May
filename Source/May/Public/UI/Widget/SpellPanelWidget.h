// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "MayWidget.h"
#include "SpellPanelWidget.generated.h"

USTRUCT(BlueprintType)
struct FSpellPanelWidgetData {
	GENERATED_BODY()

	FSpellPanelWidgetData() {}
	FSpellPanelWidgetData(UMayAbilitySystemComponent* ASC, UMayAttributeSet* AS) : AbilitySystemComponent(ASC), AttributeSet(AS) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMayAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMayAttributeSet> AttributeSet = nullptr;
};

/**
 * 
 */
UCLASS()
class MAY_API USpellPanelWidget : public UMayWidget {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="May|Widget")
	void InitWidget(const FSpellPanelWidgetData Data);

	UFUNCTION(BlueprintCallable, Category="May|Widget")
	FORCEINLINE FSpellPanelWidgetData GetWidgetData() const { return WidgetData; };

private:
	UPROPERTY()
	FSpellPanelWidgetData WidgetData;
};
