// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MayWidget.generated.h"

struct FGameplayTag;
class UMayAbilitySystemComponent;
struct FGameplayAttribute;
class UAttributeInfo;
class UMayAttributeSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeDataSignature, const FMayAttributeInfo&, Info);

/**
 * Base class for all May widgets, windows, etc.
 */
UCLASS(Blueprintable)
class MAY_API UMayWidget : public UUserWidget {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category="May|Widget")
	void OnWidgetInited();

	UPROPERTY(BlueprintAssignable, Category="May|Widget|Attributes")
	FAttributeDataSignature AttributeInfoDelegate;

protected:
	/**
	 * Widget uses this DataAsset for retrieving attribute data, defined by game designers 
	 */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;

	void SubscribeToAttribute(UMayAbilitySystemComponent* ASC, UMayAttributeSet* AS, FGameplayTag AttributeTag, FGameplayAttribute Attribute) const;
	void BroadcastAttribute(const UMayAttributeSet* AS, FGameplayTag AttributeTag, const FGameplayAttribute& Attribute) const;
};
