// Red Beat, 2023

#include "UI/Widget/PlayerInfoWidget.h"
#include "Character/EnnieCharacter.h"

void UPlayerInfoWidget::InitWidget(const FPlayerInfoWidgetData Data) {
	WidgetData = Data;

	WidgetData.OwnerPlayer->OnExperienceChangedDelegate.AddLambda([this](const float NewLevel, const int32 ExperienceDelta)
	{
		OnExperienceChanged(NewLevel, ExperienceDelta);
	});

	WidgetData.OwnerPlayer->OnLevelChangedDelegate.AddLambda([this](const float NewLevel)
	{
		OnLevelChanged(NewLevel);
	});

	OnExperienceChanged(WidgetData.OwnerPlayer->GetLevel(), 0); //broadcasting initial values

	OnWidgetInited();
}
