// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MayWidget.h"
#include "Engine/DataTable.h"
#include "OverlayWidget.generated.h"

class AEnnieCharacter;

USTRUCT(BlueprintType)
struct FUINotificationWidgetRow : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UMayWidget> NotificationWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> Image = nullptr;
};

USTRUCT(BlueprintType)
struct FOverlayWidgetData {
	GENERATED_BODY()

	FOverlayWidgetData() {}
	FOverlayWidgetData(UMayAbilitySystemComponent* ASC, UMayAttributeSet* AS, AEnnieCharacter* C) : AbilitySystemComponent(ASC), AttributeSet(AS), OwnerPlayer(C) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMayAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMayAttributeSet> AttributeSet = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AEnnieCharacter> OwnerPlayer = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUINotificationWidgetRowSignature, FUINotificationWidgetRow, Row);

/**
 * 
 */
UCLASS(Blueprintable)
class MAY_API UOverlayWidget : public UMayWidget {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="May|Widget")
	void InitWidget(const FOverlayWidgetData Data);

	UFUNCTION(BlueprintCallable, Category="May|Widget")
	FORCEINLINE FOverlayWidgetData GetWidgetData() const { return WidgetData; };

	UFUNCTION(BlueprintImplementableEvent, Category="May|UINotifications")
	void OnUINotificationMessage(FUINotificationWidgetRow Data);

protected:
	// data table with configured info about possible UI notifications
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="May|Widget")
	TObjectPtr<UDataTable> NotificationsWidgetDataTable;

	void GameplayEffectAssetTagApplied(const FGameplayTagContainer& Data);

	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
	
private:
	UPROPERTY()
	FOverlayWidgetData WidgetData;
};

template <typename T>
T* UOverlayWidget::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag) {
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
