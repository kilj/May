// Red Beat, 2023

#include "AbilitySystem/Data/AttributeInfo.h"

#include "Utils/MayLogChannels.h"

FMayAttributeInfo UAttributeInfo::FindAttributeInfo(const FGameplayTag& Tag, const bool bLogNotFound) const {
	for (const auto Element : Info) {
		if (Element.Tag.MatchesTagExact(Tag))
			return Element;
	}

	if (bLogNotFound)
		UE_LOG(LogMayAbilitySystem, Warning, TEXT("Can't find %s in %s"), *Tag.ToString(), *GetNameSafe(this));
	
	return FMayAttributeInfo();
}
