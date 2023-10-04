#include "Player/EnniePlayerState.h"

#include "AbilitySystem/MayAbilitySystemComponent.h"
#include "AbilitySystem/MayAttributeSet.h"

AEnniePlayerState::AEnniePlayerState() {
	AbilitySystemComponent = CreateDefaultSubobject<UMayAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UMayAttributeSet>("AttributeSet");
	
	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AEnniePlayerState::GetAbilitySystemComponent() const {
	return AbilitySystemComponent;
}
