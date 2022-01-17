// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponComponent.h"

#include "Pawns/HumanCharacter.h"
#include "Weapons/Weapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UWeaponComponent::SetMainWeapon(UItemInstance* ItemInstance)
{
	if (MainWeapon == ItemInstance) return false;

	MainWeapon = ItemInstance;
	return true;
}

bool UWeaponComponent::SetSecondaryWeapon(UItemInstance* ItemInstance)
{
	if (SecondaryWeapon == ItemInstance) return false;

	SecondaryWeapon = ItemInstance;
	return true;
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponsDataTable);
}

bool UWeaponComponent::EquipWeapon(UItemInstance* NewWeaponItem)
{
	if (!NewWeaponItem || CurrentWeaponItemInstance == NewWeaponItem) return false;

	const auto WeaponId = NewWeaponItem->ItemId;
	const auto WeaponInfo = WeaponsDataTable->FindRow<FWeaponItem>(WeaponId, "Weapon Component");
	if (!WeaponInfo)
	{
		UE_LOG(LogWeaponComponent, Error, TEXT("Not found weapon with name [%s]"), *WeaponId.ToString());
		return false;
	}

	const auto WeaponClass = WeaponInfo->WeaponClass;
	if (CurrentWeapon)
		GetWorld()->DestroyActor(CurrentWeapon);

	CurrentWeapon = Cast<AWeapon>(GetWorld()->SpawnActor(WeaponClass));
	if (!CurrentWeapon)
	{
		UE_LOG(LogWeaponComponent, Error, TEXT("Cannot spawn "));
		return false;
	}

	CurrentWeapon->SetOwner(GetOwner());
	const auto Character = Cast<AHumanCharacter>(GetOwner());
	if (Character)
	{
		const FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, false);
		CurrentWeapon->AttachToComponent(Character->GetMesh(), Rules, WeaponSocketName);
	}
	else
	{
		UE_LOG(LogWeaponComponent, Warning, TEXT("Owner is not HumanCharacter"));
	}

	UE_LOG(LogWeaponComponent, Display, TEXT("Equip weapon successful"));
	return true;
}

void UWeaponComponent::ChangeWeapon(int Index)
{
	if (Index == CurrentWeaponIndex || Index >= Wi_Secondary) return;

	bool Result = false;
	
	switch (Index)
	{
	case Wi_Main:
		Result = EquipWeapon(MainWeapon);
		break;
	case Wi_Secondary:
		Result = EquipWeapon(SecondaryWeapon);
		break;
	default:
		UE_LOG(LogWeaponComponent, Warning, TEXT("Cannot change weapon with index [%d]"), Index);
		return;
	}


	CurrentWeaponIndex = Index;
	UE_LOG(LogWeaponComponent, Display, TEXT("Change weapon successful"));
}

