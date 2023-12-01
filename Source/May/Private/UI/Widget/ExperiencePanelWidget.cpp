// Red Beat, 2023

#include "UI/Widget/ExperiencePanelWidget.h"

void UExperiencePanelWidget::InitWidget(const FExperiencePanelWidgetData Data) {
	WidgetData = Data;

	OnWidgetInited();
}
