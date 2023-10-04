#include "UI/WIdgetController/MayWidgetController.h"

void UMayWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& Params) {
	PlayerController = Params.PlayerController;
	PlayerState = Params.PlayerState;
	AbilitySystemComponent = Params.AbilitySystemComponent;
	AttributeSet = Params.AttributeSet;
}
