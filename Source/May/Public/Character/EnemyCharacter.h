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

	//ILevelInterface
	virtual int32 GetLevel() override;
	//end of ILevelInterface

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy Defaults")
	int32 Level = 1;
	
	bool IsHighlighted = false;

	virtual void InitAbilityActorInfo() override;

};
