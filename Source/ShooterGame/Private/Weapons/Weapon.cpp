// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Weapon.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	SetRootComponent(Mesh);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(LocomotionAsset);
}

void AWeapon::Fire()
{
}

void AWeapon::Reload()
{
}

