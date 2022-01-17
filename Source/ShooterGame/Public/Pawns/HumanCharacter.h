// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HumanCharacter.generated.h"

UCLASS()
class SHOOTERGAME_API AHumanCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AHumanCharacter();

	UFUNCTION(BlueprintCallable)
	class ULocomotionDataAsset* GetLocomotion() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UWeaponComponent* WeaponComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStorageComponent* StorageComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class ULocomotionDataAsset* DefaultLocomotionAsset;
	
	virtual void BeginPlay() override;
	virtual void Interact();

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
