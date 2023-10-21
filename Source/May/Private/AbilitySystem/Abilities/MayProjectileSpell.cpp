// Red Beat, 2023

#include "AbilitySystem/Abilities/MayProjectileSpell.h"

#include "Core/Interfaces/CombatActorInterface.h"
#include "Projectiles/MayProjectile.h"

void UMayProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) {
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	//if server
	if (HasAuthority(&ActivationInfo)) {
		checkf(ProjectileClass, TEXT("Can't spawn projectile because of Projectile class on GA is null"));
		
		ICombatActorInterface* CombatActor = Cast<ICombatActorInterface>(GetAvatarActorFromActorInfo());
		const FTransform SpawnTransform = FTransform(CombatActor != nullptr ? CombatActor->GetProjectileSpawnPosition() : FVector());
		const auto Owner = GetOwningActorFromActorInfo();

		const auto Projectile = GetWorld()->SpawnActorDeferred<AMayProjectile>(ProjectileClass, SpawnTransform, Owner, Cast<APawn>(Owner), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		//TODO: give projectile GESpec for damage
		Projectile->FinishSpawning(SpawnTransform);
	}
}
