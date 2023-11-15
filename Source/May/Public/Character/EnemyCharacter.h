#pragma once

#include "CoreMinimal.h"
#include "MayCharacterBase.h"
#include "AbilitySystem/Data/EnemyTypeInfo.h"
#include "Character/Interfaces/HighlightInterface.h"
#include "EnemyCharacter.generated.h"

class AMayAIController;
class UBehaviorTree;
struct FGameplayTag;
enum class EEnemyType : uint8;

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

	//ICombatActorInterface
	virtual void Server_Die() override;
	//end of ICombatActorInterface

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	void OnTagChanged(const FGameplayTag Tag, int32 NewTagCount);

	//TODO: maybe it's better to have enum here or something like that?
	UPROPERTY(BlueprintReadOnly, Category="State")
	bool bHitReacting = false;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy Defaults")
	EEnemyType EnemyType = EEnemyType::GoblinMelee;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AMayAIController> MayAIController;
	
	bool IsHighlighted = false;

	virtual void InitAbilityActorInfo() override;
};
