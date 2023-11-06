// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DamageTextComponent.generated.h"

USTRUCT(BlueprintType)
struct FUIDamageData {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	bool bIsBlockedHit = false;

	UPROPERTY(BlueprintReadOnly)
	bool bIsCriticalHit = false;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MAY_API UDamageTextComponent : public UWidgetComponent {
	GENERATED_BODY()

public:
	UDamageTextComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowDamageText(float Damage, FUIDamageData DamageData);

protected:
	virtual void BeginPlay() override;

};
