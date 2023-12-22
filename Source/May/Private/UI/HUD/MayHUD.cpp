#include "UI/HUD/MayHUD.h"
#include "AbilitySystem/MayAbilitySystemComponent.h"
#include "AbilitySystem/MayAttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/OverlayWidget.h"

void AMayHUD::InitOverlay(UAbilitySystemComponent* ASC, UAttributeSet* AS, AEnnieCharacter* OwnerPlayer) {
	checkf(OverlayWidgetClass, TEXT("Overlay widget class uninited."));
	
	OverlayWidget = CreateWidget<UOverlayWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget->InitWidget(FOverlayWidgetData(Cast<UMayAbilitySystemComponent>(ASC), Cast<UMayAttributeSet>(AS), OwnerPlayer));
	
	OverlayWidget->AddToViewport();
}
