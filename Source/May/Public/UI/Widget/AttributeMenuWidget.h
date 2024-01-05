// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "MayWidget.h"
#include "AttributeMenuWidget.generated.h"

class AEnniePlayerState;

USTRUCT(BlueprintType)
struct FAttributeMenuWidgetData {
	GENERATED_BODY()

	FAttributeMenuWidgetData() {}
	FAttributeMenuWidgetData(AEnniePlayerState* PS) : PlayerState(PS) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AEnniePlayerState> PlayerState = nullptr;
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

	UFUNCTION(BlueprintImplementableEvent, Category="May|Widget")
	void OnAttributePointsChanged(const int32 NewPoints);

	UFUNCTION(BlueprintImplementableEvent, Category="May|Widget")
	void OnSpellPointsChanged(const int32 NewPoints);

private:
	UPROPERTY()
	FAttributeMenuWidgetData WidgetData;
};
