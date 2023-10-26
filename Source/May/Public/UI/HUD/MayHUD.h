#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MayHUD.generated.h"

class UMayWidget;
class UOverlayWidget;
class UAttributeWindowWidgetController;
class UAttributeSet;
class UAbilitySystemComponent;
class UOverlayWidgetController;
class UMayUserWidget;
struct FWidgetControllerParams;

/**
 * 
 */
UCLASS()
class MAY_API AMayHUD : public AHUD {
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UOverlayWidget> OverlayWidget;

	//UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& Params);
	//UAttributeWindowWidgetController* GetAttributeWindowWidgetController(const FWidgetControllerParams& Params);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

private:
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidget> OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeWindowWidgetController> AttributeWindowWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMayUserWidget> AttributeWindowWidgetClass; //not needed

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeWindowWidgetController> AttributeWindowWidgetControllerClass;
};
