// Red Beat, 2023

#include "UI/Widget/ExperiencePanelWidget.h"
#include "Character/MayCharacter.h"
#include "Utils/MayLogChannels.h"

void UExperiencePanelWidget::InitWidget(const FExperiencePanelWidgetData Data) {
	WidgetData = Data;

	WidgetData.Character->OnExperienceChangedDelegate.AddLambda([this](const float NewLevel, const int32 ExperienceDelta)
	{
		MAY_ULOGW(this, TEXT("UExperiencePanelWidget: Called OnExperience changed: %f : +%i"), NewLevel, ExperienceDelta);
		OnExperienceChanged(NewLevel, ExperienceDelta);
	});

	WidgetData.Character->OnLevelChangedDelegate.AddLambda([this](const float NewLevel)
	{
		MAY_ULOGW(this, TEXT("UExperiencePanelWidget: Called OnLevel changed: %f"), NewLevel);
		OnLevelChanged(NewLevel);
	});

	OnWidgetInited();
}
