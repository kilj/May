// Red Beat, 2023


#include "UI/Widget/SpellPanelWidget.h"

void USpellPanelWidget::InitWidget(const FSpellPanelWidgetData Data) {
	WidgetData = Data;

	OnWidgetInited();
}