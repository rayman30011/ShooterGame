// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Structs.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class AWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAME_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	enum EWeaponIndex
	{
		Wi_Main = 0,
		Wi_Secondary = 1,
	};
	
	UWeaponComponent();

	UFUNCTION(BlueprintCallable)
	bool SetMainWeapon(UItemInstance* ItemInstance);

	UFUNCTION(BlueprintCallable)
	UItemInstance* GetMainWeapon() const { return MainWeapon; }

	UFUNCTION(BlueprintCallable)
	bool SetSecondaryWeapon(UItemInstance* ItemInstance);

	UFUNCTION(BlueprintCallable)
	UItemInstance* GetSecondaryWeapon() const { return SecondaryWeapon; }

	UFUNCTION(BlueprintCallable)
	void ChangeWeapon(int Index);

	UFUNCTION(BlueprintCallable)
	AWeapon* GetCurrentWeapon() const { return CurrentWeapon; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName WeaponSocketName = NAME_None;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UDataTable* WeaponsDataTable;
	
	virtual void BeginPlay() override;

private:
	bool EquipWeapon(UItemInstance* NewWeaponItem);

private:
	int32 CurrentWeaponIndex;
	AWeapon* CurrentWeapon = nullptr;
	UItemInstance* CurrentWeaponItemInstance;

	UItemInstance* MainWeapon;
	UItemInstance* SecondaryWeapon;
};
