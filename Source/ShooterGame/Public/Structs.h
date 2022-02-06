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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString ItemDescription;

	/* Ширина в инвентаре */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Width;

	/* Высота в инвентаре */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Height;
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


