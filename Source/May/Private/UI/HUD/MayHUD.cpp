#include "UI/HUD/MayHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/MayUserWidget.h"
#include "Utils/MayLogChannels.h"


void AMayHUD::BeginPlay() {
	Super::BeginPlay();

	OverlayWidget = CreateWidget<UMayUserWidget>(GetWorld(), OverlayWidgetClass);
	
	if (OverlayWidget)
		OverlayWidget->AddToViewport();
	else
		MAY_ULOGERROR(TEXT("OverlayWidget is null. Set link to proper overlay class in MayHUD blueprint."))
}
