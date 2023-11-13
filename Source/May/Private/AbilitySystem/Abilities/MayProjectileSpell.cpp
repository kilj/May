// Red Beat, 2023

#include "AbilitySystem/Abilities/MayProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Projectiles/MayProjectile.h"

void UMayProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) {
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

//TODO: rename to SpawnProjectileAndAttachEffect
void UMayProjectileSpell::SpawnProjectile(const TSubclassOf<AMayProjectile> ProjectileClass, const FVector& SpawnLocation, const FVector& TargetLocation) {
	//if server
	if (const auto Owner = GetOwningActorFromActorInfo(); Owner->HasAuthority()) {
		checkf(ProjectileClass, TEXT("Can't spawn projectile because of Projectile class is null"));
		
		FRotator Rotation = (TargetLocation - SpawnLocation).Rotation();
		Rotation.Pitch = 0.f; //making projectiles flies in parallel to the ground

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SpawnLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());

		const auto Projectile = GetWorld()->SpawnActorDeferred<AMayProjectile>(ProjectileClass, SpawnTransform, Owner, Cast<APawn>(GetAvatarActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		check(DamageEffectClass);
		
		const auto SourceASC = GetAbilitySystemComponentFromActorInfo();
		FGameplayEffectContextHandle EffectContext = SourceASC->MakeEffectContext();
		EffectContext.AddSourceObject(Projectile);
		EffectContext.SetAbility(this);

		const auto SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContext);

		for (auto& Pair : DamageTypes) {
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, Pair.Value.GetValueAtLevel(GetAbilityLevel()));
		}
		
		Projectile->DamageGESpecHandle = SpecHandle;
		Projectile->FinishSpawning(SpawnTransform);

	}
}