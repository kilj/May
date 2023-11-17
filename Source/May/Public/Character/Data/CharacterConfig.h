// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "CharacterConfig.generated.h"

class AMayCharacterBase;

USTRUCT(BlueprintType)
struct FCharacterAttackInfo {
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag Tag; //this attack tag //TODO: we should have ability tag here too and use it to group possible attacks
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* Montage = nullptr;

	// attack socket name (specific weapon, hand or something else)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName SocketName = FName();
};

/**
 * 
 */
UCLASS()
class MAY_API UCharacterConfig : public UDataAsset {
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Defaults")
	TArray<FCharacterAttackInfo> Attacks;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="CharacterConfig")
	FCharacterAttackInfo GetRandomAttackInfo(); //TODO: add here ability tag to select attack for this ability, not just random attack from all attacks

	/**
	 * Use it to find location of the socket, which can be used in attack ability (blade edge to deal melee damage, staff tip to spawn fireball, etc).
	 * If character has equipped weapon, function will try get socket on weapon first. If it fails, character mesh will be checked for needed socket.
	 * @param Tag
	 * @param Character 
	 * @return Will return socket location or character's location if can't find socket.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="CharacterConfig")
	FVector GetAttackSocketLocation(const FGameplayTag& Tag, const AMayCharacterBase* Character);
};
