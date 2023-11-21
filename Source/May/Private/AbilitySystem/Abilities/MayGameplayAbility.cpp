// Red Beat, 2023

#include "AbilitySystem/Abilities/MayGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Projectiles/MayProjectile.h"
#include "Utils/MayLogChannels.h"

void UMayGameplayAbility::SpawnProjectileAndAttachEffect(const TSubclassOf<AMayProjectile> ProjectileClass, const TSubclassOf<UGameplayEffect> ImpactGEClass, TMap<FGameplayTag, FScalableFloat> DamageTypes, const FVector& SpawnLocation, const FVector& TargetLocation) {
	const auto Owner = GetOwningActorFromActorInfo();
	if (!Owner->HasAuthority()) //Owner should has network authority to call UMayGameplayAbility::SpawnProjectileAndAttachEffect
		return;
	
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

//TODO: this method works fine when HalfAngleInDegrees <= 90
void UMayGameplayAbility::SpawnPawnsInForwardConeRandom(const TSubclassOf<APawn> PawnClass, const int32 Num, const float HalfAngleInDegrees, const float MinDistance, const float MaxDistance, const bool bDrawDebug) {
	const FVector ForwardVector = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector UpVector = GetAvatarActorFromActorInfo()->GetActorUpVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const FPlane Plane = FPlane(ForwardVector, UpVector);

	if (bDrawDebug) {
		DrawDebugCone(GetWorld(), Location, ForwardVector, MinDistance, FMath::DegreesToRadians(HalfAngleInDegrees), 0.f, 12, FColor::Magenta, false, 1.f);
		DrawDebugCone(GetWorld(), Location, ForwardVector, MaxDistance, FMath::DegreesToRadians(HalfAngleInDegrees), 0.f, 12, FColor::Magenta, false, 1.f);
	}

	for (int32 i = 0; i < Num; i++) {
		const FVector RandomUnitVector = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(ForwardVector, HalfAngleInDegrees);
		const FVector Direction = FVector::VectorPlaneProject(RandomUnitVector, Plane).GetSafeNormal();
		FVector SpawnLocation = Location + Direction * FMath::RandRange(MinDistance, MaxDistance);

		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, SpawnLocation + FVector::UpVector * 400.f, SpawnLocation + FVector::DownVector * 400.f, ECC_Visibility);
		if (Hit.bBlockingHit)
			SpawnLocation = Hit.ImpactPoint; //trace down for the ground

		if (bDrawDebug)
			DrawDebugSphere(GetWorld(), SpawnLocation, 14, 4, FColor::Green, false, 1.f);

		SpawnPawnAtPosition(PawnClass, SpawnLocation);
	}
}

void UMayGameplayAbility::SpawnPawnsInForwardConeEvenly(TSubclassOf<APawn> PawnClass, int32 Num, float HalfAngleInDegrees, float MinDistance, float MaxDistance, bool bDrawDebug) {
	const FVector ForwardVector = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();

	if (bDrawDebug) {
		DrawDebugCone(GetWorld(), Location, ForwardVector, MinDistance, FMath::DegreesToRadians(HalfAngleInDegrees), 0.f, 12, FColor::Magenta, false, 1.f);
		DrawDebugCone(GetWorld(), Location, ForwardVector, MaxDistance, FMath::DegreesToRadians(HalfAngleInDegrees), 0.f, 12, FColor::Magenta, false, 1.f);
	}

	if (Num <= 0)
		return;

	const float SpreadDelta = HalfAngleInDegrees * 2.f / Num;
	const FVector SpreadRot = ForwardVector.RotateAngleAxis(-HalfAngleInDegrees + SpreadDelta * 0.5f, FVector::UpVector);

	for (int32 i = 0; i < Num; i++) {
		const FVector Direction = SpreadRot.RotateAngleAxis(SpreadDelta * i, FVector::UpVector);
		FVector SpawnLocation = Location + Direction * FMath::RandRange(MinDistance, MaxDistance);

		FHitResult Hit;
		GetWorld()->LineTraceSingleByChannel(Hit, SpawnLocation + FVector::UpVector * 400.f, SpawnLocation + FVector::DownVector * 400.f, ECC_Visibility);
		if (Hit.bBlockingHit)
			SpawnLocation = Hit.ImpactPoint; //trace down for the ground

		if (bDrawDebug)
			DrawDebugSphere(GetWorld(), SpawnLocation, 14, 4, FColor::Green, false, 1.f);

		SpawnPawnAtPosition(PawnClass, SpawnLocation);
	}

}

void UMayGameplayAbility::SpawnPawnAtPosition(TSubclassOf<APawn> PawnClass, const FVector& SpawnLocation) {
}
