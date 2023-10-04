#include "UI/HUD/MayHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/MayUserWidget.h"
#include "UI/WIdgetController/OverlayWidgetController.h"


UOverlayWidgetController* AMayHUD::GetOverlayWidgetController(const FWidgetControllerParams& Params) {
	if (OverlayWidgetController == nullptr) {
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(Params);
	}

	return OverlayWidgetController;
}

void AMayHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS) {
	checkf(OverlayWidgetClass, TEXT("Overlay widget class uninited."));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay widget controller class uninited."));
	
	OverlayWidget = CreateWidget<UMayUserWidget>(GetWorld(), OverlayWidgetClass);

	const FWidgetControllerParams Params(PC, PS, ASC, AS);
	OverlayWidget->SetWidgetController(GetOverlayWidgetController(Params));
	
	OverlayWidget->AddToViewport();
}