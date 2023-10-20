// Red Beat, 2023

#include "Input/MayInputConfig.h"
#include "Utils/MayLogChannels.h"

const UInputAction* UMayInputConfig::FindAbilityInputActionForTag(const FGameplayTag& Tag, const bool bLogNotFound) const {
	for (const auto [EAction, ETag] : AbilityInputActions) {
		if (EAction && ETag.MatchesTagExact(Tag))
			return EAction;
	}

	if (bLogNotFound)
		UE_LOG(LogMay, Warning, TEXT("Can't find %s in %s"), *Tag.ToString(), *GetNameSafe(this));
	
	return nullptr;
}
