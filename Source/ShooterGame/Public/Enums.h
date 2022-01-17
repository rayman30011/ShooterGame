#pragma once

#include "Enums.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None = 0 UMETA(DisplayName = "None"), 
	Weapon UMETA(DisplayName = "Weapon"),
	Clothing UMETA(DisplayName = "Clothing"),
	Food UMETA(DisplayName = "Clothing")
};