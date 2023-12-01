// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "MayWidget.h"
#include "ExperiencePanelWidget.generated.h"

USTRUCT(BlueprintType)
struct FExperiencePanelWidgetData {
	GENERATED_BODY()

	FExperiencePanelWidgetData() {}
	FExperiencePanelWidgetData(UMayAbilitySystemComponent* ASC, UMayAttributeSet* AS) : AbilitySystemComponent(ASC), AttributeSet(AS) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMayAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMayAttributeSet> AttributeSet = nullptr;
};

/**
 * 
 */
UCLASS()
class MAY_API UExperiencePanelWidget : public UMayWidget {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="May|Widget")
	void InitWidget(const FExperiencePanelWidgetData Data);

	UFUNCTION(BlueprintCallable, Category="May|Widget")
	FORCEINLINE FExperiencePanelWidgetData GetWidgetData() const { return WidgetData; };

private:
	UPROPERTY()
	FExperiencePanelWidgetData WidgetData;
};
