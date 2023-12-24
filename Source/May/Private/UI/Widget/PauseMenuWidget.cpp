// Red Beat, 2023


#include "UI/Widget/PauseMenuWidget.h"

void UPauseMenuWidget::InitWidget(const FPauseMenuWidgetData Data) {
	WidgetData = Data;
	
	OnWidgetInited();
}