#include "Character/EnemyCharacter.h"

#include "AbilitySystem/MayAbilitySystemComponent.h"
#include "AbilitySystem/MayAttributeSet.h"
#include "AbilitySystem/MayGameplayTags.h"
#include "AbilitySystem/Utils/MayAbilitySystemLibrary.h"
#include "AI/MayAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Utils/MayLogChannels.h"

AEnemyCharacter::AEnemyCharacter() {
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UMayAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UMayAttributeSet>("AttributeSet");

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
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

void AEnemyCharacter::Die() {
	MAY_ULOG(TEXT("%s died..."), *GetActorNameOrLabel());
	
	SetLifeSpan(5.f);
	
	Super::Die();
}

void AEnemyCharacter::BeginPlay() {
	Super::BeginPlay();

	InitAbilityActorInfo();

	if (HasAuthority()) {
		UMayAbilitySystemLibrary::InitEnemyDefaultAttributes(GetWorld(), GetAbilitySystemComponent(), EnemyType, GetLevel());
		UMayAbilitySystemLibrary::InitEnemyDefaultAbilities(GetWorld(), GetAbilitySystemComponent());
	}

	AbilitySystemComponent->RegisterGameplayTagEvent(FMayGameplayTags::Get().EffectsHitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ThisClass::OnTagChanged);
}

void AEnemyCharacter::InitAbilityActorInfo() {
	Super::InitAbilityActorInfo();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	Cast<UMayAbilitySystemComponent>(AbilitySystemComponent)->OnAbilityActorInfoSet();
}

void AEnemyCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyCharacter::PossessedBy(AController* NewController) {
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	
	MayAIController = Cast<AMayAIController>(NewController);
	MayAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	MayAIController->RunBehaviorTree(BehaviorTree);

	const auto EType = UMayAbilitySystemLibrary::GetEnemyTypeInfo(GetWorld(), EnemyType);

	MayAIController->GetBlackboardComponent()->SetValueAsEnum(FName("AttackType"), static_cast<uint8>(EType.AttackType));
}

void AEnemyCharacter::OnTagChanged(const FGameplayTag Tag, const int32 NewTagCount) {
	bHitReacting = Tag.MatchesTagExact(FMayGameplayTags::Get().EffectsHitReact) && NewTagCount > 0; //play hit react montage
	MayAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsHitReacting"), bHitReacting);
}
