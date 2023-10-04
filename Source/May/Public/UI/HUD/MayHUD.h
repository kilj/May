#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MayHUD.generated.h"

class UMayUserWidget;
/**
 * 
 */
UCLASS()
class MAY_API AMayHUD : public AHUD {
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UMayUserWidget> OverlayWidget;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMayUserWidget> OverlayWidgetClass;
};
