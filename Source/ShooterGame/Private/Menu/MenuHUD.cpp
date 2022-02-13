// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/MenuHUD.h"

#include "ShooterGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Menu/AuthWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogMenuHud, All, All);

void AMenuHUD::BeginPlay()
{
	Widgets.Add(EMenuState::Auth, CreateWidget<UUserWidget>(GetWorld(), AuthWidgetClass));
	Widgets.Add(EMenuState::MainMenu, CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass));
	Widgets.Add(EMenuState::Player, CreateWidget<UUserWidget>(GetWorld(), PlayerWidgetClass));

	UAuthWidget* AuthWidget = Cast<UAuthWidget>(Widgets[EMenuState::Auth]);
	if (AuthWidget)
	{
		AuthWidget->OnAuthorize.AddDynamic(this, &AMenuHUD::OnAuthorized);
	}

	for (const auto WidgetPair: Widgets)
	{
		const auto Widget = WidgetPair.Value;
		if (!Widget) continue;

		Widget->AddToViewport();
		Widget->SetVisibility(ESlateVisibility::Hidden);
	}

	ChangeState(EMenuState::Auth);
}

void AMenuHUD::ChangeState(EMenuState State)
{
	if (!IsAuthorized && State != EMenuState::Auth)
	{
		UE_LOG(LogMenuHud, Warning, TEXT("Cand change state, Not authorized"));
		return;
	}
	
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}
    
	CurrentWidget = Widgets.Contains(State) ? Widgets[State] : nullptr;
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMenuHUD::OnAuthorized()
{
	IsAuthorized = true;
	ChangeState(EMenuState::MainMenu);
}

