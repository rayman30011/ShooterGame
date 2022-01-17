// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "HumanCharacter.h"

#include "FPSPlayerCharacter.generated.h"

/**
 * 
 */

class AWeapon;

UCLASS()
class SHOOTERGAME_API AFPSPlayerCharacter : public AHumanCharacter
{
	GENERATED_BODY()
public:
	AFPSPlayerCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UCameraComponent* Camera;

	virtual void BeginPlay() override;
	virtual void Interact() override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);

	void LookUp(float Value);
	void LookRight(float Value);
};
