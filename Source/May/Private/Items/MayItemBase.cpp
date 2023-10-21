#include "Items/MayItemBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "Utils/MayLogChannels.h"

AMayItemBase::AMayItemBase() {
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AMayItemBase::BeginPlay() {
	Super::BeginPlay();
}

//TODO: move to function library
FActiveGameplayEffectHandle AMayItemBase::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass) {
	const auto TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return false;

	if (GameplayEffectClass == nullptr) {
		MAY_ULOGERROR(TEXT("Can't apply GE to target, because GE class is null"));
		return false;
	}
	
	FGameplayEffectContextHandle EffectContext = TargetASC->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle EffectSpec = TargetASC->MakeOutgoingSpec(GameplayEffectClass, Level, EffectContext);
	return TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get());
}

void AMayItemBase::OnBeginOverlap(AActor* TargetActor) {
}

void AMayItemBase::OnEndOverlap(AActor* TargetActor) {
}

