// Red Beat, 2023

#include "Character/Data/LevelInfo.h"

#include "Utils/MayLogChannels.h"

void ULevelInfo::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
	const int32 Index = PropertyChangedEvent.GetArrayIndex(TEXT("Levels"));
	if (Index >= 0) {
		for (int i = 0; i < Levels.Num(); ++i) {
			Levels[i].Level = i + 1;
		}
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

float ULevelInfo::GetLevel(const int32 Experience) {
	auto Level = 0;
	auto Fraction = 0.f;
	auto XP = Experience;
	for (const auto Info : Levels) {
		if (XP < Info.Experience) {
			Fraction = static_cast<float>(XP) / static_cast<float>(Info.Experience);
			break;
		}
		XP -= Info.Experience;
		Level++;
	}

	return Level + Fraction;
}

int32 ULevelInfo::GetExperience(const float Level) {
	const auto Lvl = FMath::FloorToInt(Level);
	const auto Fraction = Level - Lvl;
	int32 Experience = 0;
	for (int i = 0; i < Lvl; i++) {
		Experience += Levels[i].Experience;
	}

	Experience += FMath::RoundToInt(Levels[Lvl].Experience * Fraction);

	return Experience;
}

FLevelInfoDefault ULevelInfo::GetLevelInfo(const float Level) {
	const int32 Lvl = FMath::FloorToInt(Level);
	
	if (Levels.Num() >= Lvl || Lvl <= 0) {
		MAY_ULOGE(this, TEXT("Can't get level info for level %i"), Lvl);
		return FLevelInfoDefault();
	}

	return Levels[Lvl];
}
