// Red Beat, 2023

#include "AbilitySystem/Utils/MayAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Player/EnniePlayerState.h"
#include "UI/HUD/MayHUD.h"
#include "UI/WIdgetController/MayWidgetController.h"

UOverlayWidgetController* UMayAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject) {
	if (const auto PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0)) {
		if (const auto MayHUD = Cast<AMayHUD>(PC->GetHUD())) {
			const auto PS = PC->GetPlayerState<AEnniePlayerState>();
			const auto ASC = PS->GetAbilitySystemComponent();
			const auto AS = PS->GetAttributeSet();

			const FWidgetControllerParams Params (PC, PS, ASC, AS);
			return MayHUD->GetOverlayWidgetController(Params);
		}
	}

	return nullptr;
}

UAttributeWindowWidgetController* UMayAbilitySystemLibrary::GetAttributeWindowWidgetController(const UObject* WorldContextObject) {
	if (const auto PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0)) {
		if (const auto MayHUD = Cast<AMayHUD>(PC->GetHUD())) {
			const auto PS = PC->GetPlayerState<AEnniePlayerState>();
			const auto ASC = PS->GetAbilitySystemComponent();
			const auto AS = PS->GetAttributeSet();

			const FWidgetControllerParams Params (PC, PS, ASC, AS);
			return MayHUD->GetAttributeWindowWidgetController(Params);
		}
	}

	return nullptr;
}
