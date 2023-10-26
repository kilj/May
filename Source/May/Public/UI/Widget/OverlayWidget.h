// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "MayWidget.h"
#include "Engine/DataTable.h"
#include "OverlayWidget.generated.h"

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
	FOverlayWidgetData(UMayAbilitySystemComponent* ASC, UMayAttributeSet* AS) : AbilitySystemComponent(ASC), AttributeSet(AS) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMayAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UMayAttributeSet> AttributeSet = nullptr;
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

	UPROPERTY(BlueprintAssignable, Category="GAS|Messages")
	FUINotificationWidgetRowSignature NotificationsWidgetRowDelegate; //TODO: delete

	UFUNCTION(BlueprintImplementableEvent, Category="May|UINotifications")
	void OnUINotificationMessage(FUINotificationWidgetRow Data);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="May|Widget|Data")
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
