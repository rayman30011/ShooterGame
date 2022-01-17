// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Weapon.generated.h"

UCLASS()
class SHOOTERGAME_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWeapon();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMeshComponent* Mesh;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class ULocomotionDataAsset* LocomotionAsset;
	
	virtual void BeginPlay() override;
	
public:
	class ULocomotionDataAsset* GetLocomotion() const { return LocomotionAsset; }
	void Fire();
	void Reload();
};
