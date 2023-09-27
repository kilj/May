#pragma once

#include "CoreMinimal.h"
#include "MayCharacterBase.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class MAY_API AEnemyCharacter : public AMayCharacterBase {
	GENERATED_BODY()

public:
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
