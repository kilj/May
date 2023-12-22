#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MayHUD.generated.h"

class AEnnieCharacter;
class UMayWidget;
class UOverlayWidget;
class UAttributeSet;
class UAbilitySystemComponent;
class UMayUserWidget;

/**
 * 
 */
UCLASS()
class MAY_API AMayHUD : public AHUD {
	GENERATED_BODY()

public:
	void InitOverlay(UAbilitySystemComponent* ASC, UAttributeSet* AS, AEnnieCharacter* C);

private:
	UPROPERTY()
	TObjectPtr<UOverlayWidget> OverlayWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidget> OverlayWidgetClass;
};
