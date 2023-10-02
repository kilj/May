#pragma once

#include "CoreMinimal.h"
#include "MayCharacterBase.h"
#include "Core/Interfaces/HighlightInterface.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class MAY_API AEnemyCharacter : public AMayCharacterBase, public IHighlightInterface {
	GENERATED_BODY()

public:
	AEnemyCharacter();

	//IHighlightInterface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	//end of IHighlightInterface

protected:
	virtual void BeginPlay() override;

	bool IsHighlighted = false;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
