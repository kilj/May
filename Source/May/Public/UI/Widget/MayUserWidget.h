#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MayUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MAY_API UMayUserWidget : public UUserWidget {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
