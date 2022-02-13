// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/MenuGameMode.h"

#include "Core/CorePlayerController.h"
#include "Menu/MenuHUD.h"

AMenuGameMode::AMenuGameMode()
{
	PlayerControllerClass = ACorePlayerController::StaticClass();
	HUDClass = AMenuHUD::StaticClass();
}

void AMenuGameMode::Auth()
{
	OnUserAuthorized.Broadcast();
}
