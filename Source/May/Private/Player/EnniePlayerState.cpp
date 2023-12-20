#include "Player/EnniePlayerState.h"

#include "AbilitySystem/MayAbilitySystemComponent.h"
#include "AbilitySystem/MayAttributeSet.h"
#include "Net/UnrealNetwork.h"

AEnniePlayerState::AEnniePlayerState() {
	AbilitySystemComponent = CreateDefaultSubobject<UMayAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UMayAttributeSet>("AttributeSet");
	
	NetUpdateFrequency = 100.f;
}

void AEnniePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEnniePlayerState, Level);
}

void AEnniePlayerState::OnRep_Level(const float OldLevel) {
	//MAY_ULOGW(this, TEXT("%s OnRep_Level! %f:%f"), *GetActorNameOrLabel(), Level, OldLevel);
}

UAbilitySystemComponent* AEnniePlayerState::GetAbilitySystemComponent() const {
	return AbilitySystemComponent;
}
