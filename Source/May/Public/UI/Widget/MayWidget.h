// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MayWidget.generated.h"

struct FMayAttributeInfo;
struct FGameplayTag;
struct FGameplayAttribute;
class UMayAbilitySystemComponent;
class UMayAttributeSet;
class UAttributeInfo;

/**
 * Base class for all May widgets, windows, etc.
 */
UCLASS(Blueprintable)
class MAY_API UMayWidget : public UUserWidget {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category="May|Widget")
	void OnWidgetInited(); //TODO: call before subscription/broadcasting events to bp?

	UFUNCTION(BlueprintImplementableEvent, Category="May|Widget")
	void OnAttributeInfoChanged(FMayAttributeInfo Info);

protected:
	//TODO: cache here local player?
	
	/**
	 * Widget uses this DataAsset for retrieving attribute data, defined by game designers 
	 */
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo; //TODO: use from some client class and delete here

	void SubscribeToAttribute(UMayAbilitySystemComponent* ASC, UMayAttributeSet* AS, FGameplayTag AttributeTag, const FGameplayAttribute& Attribute);
	void BroadcastAttribute(const UMayAttributeSet* AS, FGameplayTag AttributeTag, const FGameplayAttribute& Attribute);
};
