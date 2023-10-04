#include "UI/Widget/MayUserWidget.h"

void UMayUserWidget::SetWidgetController(UObject* InWidgetController) {
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
