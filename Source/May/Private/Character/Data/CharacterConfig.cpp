// Red Beat, 2023

#include "Character/Data/CharacterConfig.h"
#include "Character/MayCharacterBase.h"

FCharacterAttackInfo UCharacterConfig::GetRandomAttackInfo() {
	checkf(Attacks.Num() > 0, TEXT("Attacks array is empty"));
	
	return Attacks[FMath::RandRange(0, Attacks.Num() - 1)];
}

FVector UCharacterConfig::GetAttackSocketLocation(const FGameplayTag& Tag, const AMayCharacterBase* Character) {
	FName SocketName = FName();
	for (const auto Attack : Attacks) {
		if (Attack.Tag.MatchesTagExact(Tag)) {
			SocketName = Attack.SocketName;
			break;
		}
	}

	//check weapon socket first...
	if (Character->Weapon && Character->Weapon->DoesSocketExist(SocketName))
		return Character->Weapon->GetSocketLocation(SocketName);

	//... and the mesh at the end
	if (Character->GetMesh()->DoesSocketExist(SocketName))
		return Character->GetMesh()->GetSocketLocation(SocketName);

	return Character->GetActorLocation();
}
