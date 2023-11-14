// Red Beat, 2023

#include "AbilitySystem/Abilities/MayGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Projectiles/MayProjectile.h"
#include "Utils/MayLogChannels.h"

void UMayGameplayAbility::SpawnProjectileAndAttachEffect(const TSubclassOf<AMayProjectile> ProjectileClass, const TSubclassOf<UGameplayEffect> ImpactGEClass, TMap<FGameplayTag, FScalableFloat> DamageTypes, const FVector& SpawnLocation, const FVector& TargetLocation) {
	const auto Owner = GetOwningActorFromActorInfo();
	checkf(Owner->HasAuthority(), TEXT("Owner should has network authority to call UMayGameplayAbility::SpawnProjectileAndAttachEffect"))
	checkf(ProjectileClass, TEXT("Can't spawn projectile because of ProjectileClass is null"));
	checkf(ImpactGEClass, TEXT("Can't attach impact gameplay effect, because ImpactGEClass is null"));

	FRotator Rotation = (TargetLocation - SpawnLocation).Rotation();
	Rotation.Pitch = 0.f; //making projectiles flies in parallel to the ground

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SpawnLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());

	const auto Projectile = GetWorld()->SpawnActorDeferred<AMayProjectile>(ProjectileClass, SpawnTransform, Owner, Cast<APawn>(GetAvatarActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	const auto SourceASC = GetAbilitySystemComponentFromActorInfo();
	FGameplayEffectContextHandle EffectContext = SourceASC->MakeEffectContext();
	EffectContext.AddSourceObject(Projectile);
	EffectContext.SetAbility(this);

	const auto SpecHandle = SourceASC->MakeOutgoingSpec(ImpactGEClass, 1.f, EffectContext);

	for (auto& Pair : DamageTypes) {
		if (!Pair.Key.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Damage.Type")))) {
			MAY_ULOGW(Owner, TEXT("Gameplay tag [%s] is not a damage type tag (use Damage.Type.Something). This tag will be skipped..."), *Pair.Key.ToString())
			continue;
		}
		
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, Pair.Value.GetValueAtLevel(GetAbilityLevel()));
	}

	Projectile->DamageGESpecHandle = SpecHandle;
	Projectile->FinishSpawning(SpawnTransform);
}

void UMayGameplayAbility::ApplyEffectToActors(TArray<AActor*> TargetActors, const TSubclassOf<UGameplayEffect> ImpactGEClass, const TMap<FGameplayTag, FScalableFloat> DamageTypes) {
	for (const auto Actor : TargetActors)
		ApplyEffectToActor(Actor, ImpactGEClass, DamageTypes);
}

void UMayGameplayAbility::ApplyEffectToActor(AActor* TargetActor, const TSubclassOf<UGameplayEffect> ImpactGEClass, TMap<FGameplayTag, FScalableFloat> DamageTypes) {
	const auto Owner = GetOwningActorFromActorInfo();
	checkf(Owner->HasAuthority(), TEXT("Owner should has network authority to call UMayGameplayAbility::SpawnProjectileAndAttachEffect"))
	checkf(ImpactGEClass, TEXT("Can't apply impact gameplay effect, because ImpactGEClass is null"));

	const auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	checkf(TargetASC, TEXT("Actor [%s] hasn't Ability system component"), *TargetActor->GetActorNameOrLabel());

	const auto SourceASC = GetAbilitySystemComponentFromActorInfo();
	
	FGameplayEffectContextHandle EffectContext = SourceASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	EffectContext.SetAbility(this);

	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(ImpactGEClass, 1.f, EffectContext);

	for (auto& Pair : DamageTypes) {
		if (!Pair.Key.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Damage.Type")))) {
			MAY_ULOGW(Owner, TEXT("Gameplay tag [%s] is not a damage type tag (use Damage.Type.Something). This tag will be skipped..."), *Pair.Key.ToString())
			continue;
		}
		
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, Pair.Value.GetValueAtLevel(GetAbilityLevel()));
	}

	SourceASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);
}