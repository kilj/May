#include "AbilitySystem/MayAttributeSet.h"

#include "Net/UnrealNetwork.h"

UMayAttributeSet::UMayAttributeSet() {
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(10.f);
	InitMaxMana(100.f);
}

void UMayAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMayAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UMayAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, Health, OldHealth);
}

void UMayAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, MaxHealth, OldMaxHealth);
}

void UMayAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, Mana, OldMana);
}

void UMayAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const {
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMayAttributeSet, MaxMana, OldMaxMana);
}
