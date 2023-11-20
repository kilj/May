#include "Core/MayGameMode.h"
#include "Player/EnniePlayerController.h"
#include "UObject/ConstructorHelpers.h"

AMayGameMode::AMayGameMode() {
	PlayerControllerClass = AEnniePlayerController::StaticClass();
}
