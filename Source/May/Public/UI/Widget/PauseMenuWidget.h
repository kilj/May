// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "MayWidget.h"
#include "PauseMenuWidget.generated.h"

USTRUCT(BlueprintType)
struct FPauseMenuWidgetData {
	GENERATED_BODY()

	FPauseMenuWidgetData() {}
};

/**
 * 
 */
UCLASS()
class MAY_API UPauseMenuWidget : public UMayWidget {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="May|Widget")
	void InitWidget(const FPauseMenuWidgetData Data);

	UFUNCTION(BlueprintCallable, Category="May|Widget")
	FORCEINLINE FPauseMenuWidgetData GetWidgetData() const { return WidgetData; };

private:
	UPROPERTY()
	FPauseMenuWidgetData WidgetData;
};
