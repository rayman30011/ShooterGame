// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Enums.h"
#include "GameFramework/HUD.h"
#include "MenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API AMenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> AuthWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> SelectingLevelWidgetClass;

	UFUNCTION(BlueprintCallable, Category = "Menu Functions")
	void ChangeState(EMenuState NewState);

private:
	UFUNCTION()
	void OnAuthorized();
	
private:
	UPROPERTY();
	TMap<EMenuState, UUserWidget*> Widgets;

	UPROPERTY();
	UUserWidget* CurrentWidget = nullptr;
	
	EMenuState CurrentState;

	bool IsAuthorized = false;
};
