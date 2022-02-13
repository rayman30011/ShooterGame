// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShooterGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API UShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void SetToken(FString Value) { Token = Value; }
	FString GetToken() const { return Token; }
	
private:
	FString Token;
};
