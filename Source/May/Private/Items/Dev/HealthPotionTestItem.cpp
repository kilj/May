#include "Items/Dev/HealthPotionTestItem.h"

#include "AbilitySystemInterface.h"
#include "AbilitySystem/MayAttributeSet.h"


AHealthPotionTestItem::AHealthPotionTestItem() {
}

void AHealthPotionTestItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (const auto ASI = Cast<IAbilitySystemInterface>(OtherActor)) {
		auto MayAttributeSet = Cast<UMayAttributeSet>(ASI->GetAbilitySystemComponent()->GetAttributeSet(UMayAttributeSet::StaticClass()));

		auto cMAS = const_cast<UMayAttributeSet*>(MayAttributeSet);
		cMAS->SetHealth(cMAS->GetHealth() - 10.f);
		cMAS->SetMana(cMAS->GetMana() - 5.f);
	}
}

void AHealthPotionTestItem::BeginPlay() {
	Super::BeginPlay();
	
}