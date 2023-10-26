#include "UI/HUD/MayHUD.h"
#include "AbilitySystem/MayAbilitySystemComponent.h"
#include "AbilitySystem/MayAttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/OverlayWidget.h"


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

void AMayHUD::InitOverlay(UAbilitySystemComponent* ASC, UAttributeSet* AS) {
	checkf(OverlayWidgetClass, TEXT("Overlay widget class uninited."));
	
	OverlayWidget = CreateWidget<UOverlayWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->InitWidget(FOverlayWidgetData(Cast<UMayAbilitySystemComponent>(ASC), Cast<UMayAttributeSet>(AS)));
	
	OverlayWidget->AddToViewport();
}
