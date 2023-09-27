#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MayCharacterBase.generated.h"

UCLASS(Abstract)
class MAY_API AMayCharacterBase : public ACharacter {
	GENERATED_BODY()

public:
	AMayCharacterBase();
	
protected:
	virtual void BeginPlay() override;

	// UPROPERTY()
	// TObjectPtr<USceneComponent> WeaponSocket;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(AllowPrivateAccess="true"))
	TObjectPtr<USkeletalMeshComponent> Weapon;

};
