// Red Beat, 2023

#pragma once

#include "Logging/LogMacros.h"

class UObject;

MAY_API DECLARE_LOG_CATEGORY_EXTERN(LogMay, Log, All);
MAY_API DECLARE_LOG_CATEGORY_EXTERN(LogMayExperience, Log, All);
MAY_API DECLARE_LOG_CATEGORY_EXTERN(LogMayAbilitySystem, Log, All);

MAY_API FString GetClientServerContextString(UObject* ContextObject = nullptr);

/**
 * MAY_ULOG
 *
 *   You can use this macro in any code where `Owner` evaluates to a valid UObject.
 *   The log will print with the __FUNCTION__ and __LINE__ where you write the macro,
 *   and will report `this` identity as [OwnerName]->[ThisName] in the log message.
 *   The message that you pass in (fmt, ...) is appended to the rest of the log info.
 *   
 */

#define MAY_ULOG(Owner, fmt, ...) \
UE_LOG(LogMay, Log, \
TEXT("[%s] %s:%i [%s]->[%s] %s"), \
*GetClientServerContextString(Owner), \
*FString(__FUNCTION__), __LINE__, \
*GetNameSafe(Owner), *GetNameSafe(this), \
*FString::Printf(fmt, ##__VA_ARGS__) \
)

#define MAY_ULOGW(Owner, fmt, ...) \
UE_LOG(LogMay, Warning, \
TEXT("[%s] %s:%i [%s]->[%s] %s"), \
*GetClientServerContextString(Owner), \
*FString(__FUNCTION__), __LINE__, \
*GetNameSafe(Owner), *GetNameSafe(this), \
*FString::Printf(fmt, ##__VA_ARGS__) \
)

#define MAY_ULOGE(Owner, fmt, ...) \
UE_LOG(LogMay, Error, \
TEXT("[%s] %s:%i [%s]->[%s] %s"), \
*GetClientServerContextString(Owner), \
*FString(__FUNCTION__), __LINE__, \
*GetNameSafe(Owner), *GetNameSafe(this), \
*FString::Printf(fmt, ##__VA_ARGS__) \
)