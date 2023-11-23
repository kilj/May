// Red Beat, 2023

#include "Character/Data/CharacterConfig.h"
#include "Character/MayCharacterBase.h"
#include "Utils/MayLogChannels.h"

FActionInfo UCharacterConfig::GetAttackInfo(const FGameplayTag& Tag) {
	for (const auto Attack : Attacks) {
		if (Attack.Tag.MatchesTag(Tag))
			return Attack;
	}

	return FActionInfo::Empty();
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

UNiagaraSystem* UCharacterConfig::GetHitReaction(const FGameplayTag& Tag) {
	if (HitReacts.Num() <= 0)
		MAY_ULOGW(this, TEXT("Trying to get hit reaction niagara system from empty HitReacts map. Check character's config."));

	if (HitReacts.Contains(Tag))
		return HitReacts[Tag];

	return nullptr;
}
