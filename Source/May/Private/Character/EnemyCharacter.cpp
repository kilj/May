#include "Character/EnemyCharacter.h"

#include "AbilitySystem/MayAbilitySystemComponent.h"
#include "AbilitySystem/MayAttributeSet.h"
#include "AbilitySystem/MayGameplayTags.h"
#include "AbilitySystem/Utils/MayAbilitySystemLibrary.h"
#include "Utils/MayLogChannels.h"

AEnemyCharacter::AEnemyCharacter() {
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UMayAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UMayAttributeSet>("AttributeSet");
}

void AEnemyCharacter::HighlightActor() {
	IsHighlighted = true;

	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->CustomDepthStencilValue = 250;
	Weapon->SetRenderCustomDepth(true);
	Weapon->CustomDepthStencilValue = 250;
}

void AEnemyCharacter::UnHighlightActor() {
	IsHighlighted = false;

	GetMesh()->SetRenderCustomDepth(false);
	GetMesh()->CustomDepthStencilValue = 0;
	Weapon->SetRenderCustomDepth(false);
	Weapon->CustomDepthStencilValue = 0;
}

int32 AEnemyCharacter::GetLevel() {
	return Level;
}

void AEnemyCharacter::BeginPlay() {
	Super::BeginPlay();

	InitAbilityActorInfo();

	UMayAbilitySystemLibrary::InitEnemyDefaultAttributes(GetWorld(), GetAbilitySystemComponent(), EnemyType, GetLevel());
	UMayAbilitySystemLibrary::InitEnemyDefaultAbilities(GetWorld(), GetAbilitySystemComponent());

	// InitDefaultAttributes(DefaultPrimaryAttributes); //init default primary attributes on server, so they will be replicated to clients...
	// InitDefaultAttributes(DefaultSecondaryAttributes); //... and do the same with secondary attributes
	// InitDefaultAttributes(DefaultVitalAttributes); //... in the end we should set initial values for Health/Mana

	//AddStartupAbilities();

	AbilitySystemComponent->RegisterGameplayTagEvent(FMayGameplayTags::Get().EffectsHitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::OnTagChanged);
}

void AEnemyCharacter::InitAbilityActorInfo() {
	Super::InitAbilityActorInfo();

	MAY_ULOG(TEXT("Init ability actor info on enemy: %s"), *GetActorNameOrLabel());
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	Cast<UMayAbilitySystemComponent>(AbilitySystemComponent)->OnAbilityActorInfoSet();
}

void AEnemyCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// if (IsHighlighted)
	// 	DrawDebugSphere(GetWorld(), GetActorLocation(), 40, 12, FColor::Red);
}

void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyCharacter::OnTagChanged(const FGameplayTag Tag, const int32 NewTagCount) {
	bHitReacting = Tag.MatchesTagExact(FMayGameplayTags::Get().EffectsHitReact) && NewTagCount > 0; //play hit react montage
}
