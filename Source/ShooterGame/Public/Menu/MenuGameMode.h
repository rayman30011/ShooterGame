// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MenuGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUserAuthorize);

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API AMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMenuGameMode();
	
	FOnUserAuthorize OnUserAuthorized;

private:
	void Auth();
};
