// Red Beat, 2023

#pragma once

#include "GameplayEffectTypes.h"
#include "MayAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FMayGameplayEffectContext : public FGameplayEffectContext {
	GENERATED_BODY()

public:
	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const override {
		return StaticStruct();
	}

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FMayGameplayEffectContext* Duplicate() const override {
		FMayGameplayEffectContext* NewContext = new FMayGameplayEffectContext();
		*NewContext = *this;
		NewContext->AddActors(Actors);
		if (GetHitResult()) {
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}
	
	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;

	bool IsBlockHit() const {return bIsBlockedHit;}
	bool IsCriticalHit() const {return bIsCriticalHit;}

	void SetIsBlockHit(const bool bInIsBlockHit) {bIsBlockedHit = bInIsBlockHit;}
	void SetIsCriticalHit(const bool bInIsCriticalHit) {bIsCriticalHit = bInIsCriticalHit;}

protected:
	UPROPERTY()
	bool bIsBlockedHit = false;

	UPROPERTY()
	bool bIsCriticalHit = false;
};

template <>
struct TStructOpsTypeTraits<FMayGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FMayGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true // Necessary so that TSharedPtr<FHitResult> Data is copied around
	};
};