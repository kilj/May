// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "MayWidgetController.h"
#include "AttributeWindowWidgetController.generated.h"

class UAttributeInfo;
struct FMayAttributeInfo;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FMayAttributeInfo&, Info);

/**
 * AttributeWindow widget controller
 */
UCLASS(BlueprintType, Blueprintable)
class MAY_API UAttributeWindowWidgetController : public UMayWidgetController {
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;
};
