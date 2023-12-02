// Red Beat, 2023

#include "AbilitySystem/Data/AbilityInfo.h"

#include "Utils/MayLogChannels.h"

FMayAbilityInfo UAbilityInfo::GetAbilityInfo(const FGameplayTag& Tag, const bool bLogNotFound) const {
	//TODO: check usability and change TArray to TMap if Info will have a lot of abilities or TArray has poor usability
	for (const auto Ability : Info) {
		if (Ability.Tag.MatchesTag(Tag))
			return Ability;
	}

	if (bLogNotFound)
		UE_LOG(LogMayAbilitySystem, Warning, TEXT("Can't find ability info for tag %s in %s"), *Tag.ToString(), *GetNameSafe(this));

	return FMayAbilityInfo();
}
