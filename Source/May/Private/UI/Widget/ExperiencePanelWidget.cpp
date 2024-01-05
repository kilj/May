// Red Beat, 2023

#include "UI/Widget/ExperiencePanelWidget.h"

#include "Character/EnnieCharacter.h"
#include "Utils/MayLogChannels.h"

void UExperiencePanelWidget::InitWidget(const FExperiencePanelWidgetData Data) {
	WidgetData = Data;

	WidgetData.OwnerPlayer->OnExperienceChangedDelegate.AddLambda([this](const float NewLevel, const int32 ExperienceDelta)
	{
		MAY_ULOG(this, TEXT("UExperiencePanelWidget: Called OnExperience changed: %f : +%i"), NewLevel, ExperienceDelta);
		OnExperienceChanged(NewLevel, ExperienceDelta);
	});

	WidgetData.OwnerPlayer->OnLevelChangedDelegate.AddLambda([this](const float NewLevel)
	{
		MAY_ULOG(this, TEXT("UExperiencePanelWidget: Called OnLevel changed: %f"), NewLevel);
		OnLevelChanged(NewLevel);
	});

	//OnLevelChanged(WidgetData.OwnerPlayer->GetLevel()); //broadcasting initial values
	OnExperienceChanged(WidgetData.OwnerPlayer->GetLevel(), 0); //broadcasting initial values

	OnWidgetInited();
}
