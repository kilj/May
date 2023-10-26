#include "UI/HUD/MayHUD.h"

#include "AbilitySystem/MayAbilitySystemComponent.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/OverlayWidget.h"
#include "UI/WIdgetController/OverlayWidgetController.h"


// UOverlayWidgetController* AMayHUD::GetOverlayWidgetController(const FWidgetControllerParams& Params) {
// 	if (OverlayWidgetController == nullptr) {
// 		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
// 		OverlayWidgetController->SetWidgetControllerParams(Params);
// 		OverlayWidgetController->BindCallbacksToDependencies();
//
// 	}
//
// 	return OverlayWidgetController;
// }
//
// UAttributeWindowWidgetController* AMayHUD::GetAttributeWindowWidgetController(const FWidgetControllerParams& Params) {
// 	if (AttributeWindowWidgetController == nullptr) {
// 		AttributeWindowWidgetController = NewObject<UAttributeWindowWidgetController>(this, AttributeWindowWidgetControllerClass);
// 		AttributeWindowWidgetController->SetWidgetControllerParams(Params);
// 		AttributeWindowWidgetController->BindCallbacksToDependencies();
//
// 	}
//
// 	return AttributeWindowWidgetController;
// }

void AMayHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS) {
	checkf(OverlayWidgetClass, TEXT("Overlay widget class uninited."));
	//checkf(OverlayWidgetControllerClass, TEXT("Overlay widget controller class uninited."));
	
	OverlayWidget = CreateWidget<UOverlayWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->InitWidget(FOverlayWidgetData(Cast<UMayAbilitySystemComponent>(ASC), Cast<UMayAttributeSet>(AS)));

	// const FWidgetControllerParams Params(PC, PS, ASC, AS);
	// const auto OWC = GetOverlayWidgetController(Params);

	// OverlayWidget->SetWidgetController(OWC);
	// OWC->BroadcastInitialValues();
	
	OverlayWidget->AddToViewport();
}
