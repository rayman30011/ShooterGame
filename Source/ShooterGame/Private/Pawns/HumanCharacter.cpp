// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterGame/Public/Pawns/HumanCharacter.h"

#include "Actors/Item.h"
#include "Components/StorageComponent.h"
#include "Components/WeaponComponent.h"
#include "Weapons/Weapon.h"

// Sets default values
AHumanCharacter::AHumanCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponComp = CreateDefaultSubobject<UWeaponComponent>("WeaponComp");
	StorageComp = CreateDefaultSubobject<UStorageComponent>("StorageComp");
}

ULocomotionDataAsset* AHumanCharacter::GetLocomotion() const
{
	if (WeaponComp->GetCurrentWeapon())
		return WeaponComp->GetCurrentWeapon()->GetLocomotion();
	
	return DefaultLocomotionAsset;
}

// Called when the game starts or when spawned
void AHumanCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AHumanCharacter::Interact()
{
}

void AHumanCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

