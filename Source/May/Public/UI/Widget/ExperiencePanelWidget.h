// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "MayWidget.h"
#include "ExperiencePanelWidget.generated.h"

class AMayCharacterBase;

USTRUCT(BlueprintType)
struct FExperiencePanelWidgetData {
	GENERATED_BODY()

	FExperiencePanelWidgetData() {}
	FExperiencePanelWidgetData(UMayAbilitySystemComponent* ASC, UMayAttributeSet* AS) : AbilitySystemComponent(ASC), AttributeSet(AS) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMayAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMayAttributeSet> AttributeSet = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AMayCharacterBase> Character = nullptr;
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

	UFUNCTION(BlueprintImplementableEvent, Category="May|Widget")
	void OnExperienceChanged(const float NewLevel, const int32 ExperienceDelta);

	UFUNCTION(BlueprintImplementableEvent, Category="May|Widget")
	void OnLevelChanged(const float NewLevel);

private:
	UPROPERTY()
	FExperiencePanelWidgetData WidgetData;
};
