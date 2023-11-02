// Red Beat, 2023

#include "MayAbilitySystemGlobals.h"
#include "AbilitySystem/MayAbilityTypes.h"

FGameplayEffectContext* UMayAbilitySystemGlobals::AllocGameplayEffectContext() const {
	return new FMayGameplayEffectContext(); //this raw pointer will be stored inside shared ptr anyways (and that's GAS recommended approach)
}
