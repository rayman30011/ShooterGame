#pragma once

#include "Enums.h"
#include "Engine/DataTable.h"
#include "Templates/SubclassOf.h"
#include "Weapons/Weapon.h"

#include "Structs.generated.h"

USTRUCT(BlueprintType)
struct FItemInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ItemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image;
};

USTRUCT(BlueprintType)
struct FWeaponItem : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AWeapon> WeaponClass;
};

UCLASS(Blueprintable)
class UItemInstance : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ItemId;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EItemType ItemType;
};


