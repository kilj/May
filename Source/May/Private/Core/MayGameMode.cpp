#include "Core/MayGameMode.h"
#include "..\..\Public\Player\EnniePlayerController.h"
#include "UObject/ConstructorHelpers.h"

AMayGameMode::AMayGameMode() {
	PlayerControllerClass = AEnniePlayerController::StaticClass();

	// // set default pawn class to our Blueprinted character
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/May/Assets/TopDown/Blueprints/BP_TopDownCharacter"));
	// if (PlayerPawnBPClass.Class != nullptr) {
	// 	DefaultPawnClass = PlayerPawnBPClass.Class;
	// }
	//
	// // set default controller to our Blueprinted controller
	// static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/May/Assets/TopDown/Blueprints/BP_TopDownPlayerController"));
	// if (PlayerControllerBPClass.Class != NULL) {
	// 	PlayerControllerClass = PlayerControllerBPClass.Class;
	// }
}
