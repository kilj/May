// Red Beat, 2023

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "MayInputConfig.h"
#include "MayInputComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MAY_API UMayInputComponent : public UEnhancedInputComponent {
	GENERATED_BODY()

public:
	UMayInputComponent();

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UMayInputConfig* Config, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UMayInputComponent::BindAbilityActions(const UMayInputConfig* Config, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc) {
	check(Config);

	for (const auto [Action, Tag] : Config->AbilityInputActions) {
		if (Action && Tag.IsValid()) {
			if (PressedFunc)
				BindAction(Action, ETriggerEvent::Started, Object, PressedFunc, Tag);

			if (ReleasedFunc)
				BindAction(Action, ETriggerEvent::Completed, Object, ReleasedFunc, Tag);
			
			if (HeldFunc)
				BindAction(Action, ETriggerEvent::Triggered, Object, HeldFunc, Tag);
		}
	}
}
