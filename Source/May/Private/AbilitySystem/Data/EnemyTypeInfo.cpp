// Red Beat, 2023

#include "AbilitySystem/Data/EnemyTypeInfo.h"

FEnemyTypeDefaultInfo UEnemyTypeInfo::GetEnemyTypeDefaultInfo(const EEnemyType Type) {
	return Info.FindChecked(Type);
}
