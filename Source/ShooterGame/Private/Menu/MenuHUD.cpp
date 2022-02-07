// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/MenuHUD.h"

#include "Blueprint/UserWidget.h"

void AMenuHUD::BeginPlay()
{
	Widgets.Add(EMenuState::Auth, CreateWidget<UUserWidget>(GetWorld(), AuthWidget));
	Widgets.Add(EMenuState::MainMenu, CreateWidget<UUserWidget>(GetWorld(), MainMenuWidget));
	Widgets.Add(EMenuState::Player, CreateWidget<UUserWidget>(GetWorld(), PlayerWidget));

	for (auto WidgetPair: Widgets)
	{
		const auto Widget = WidgetPair.Value;
		if (!Widget) continue;

		Widget->AddToViewport();
		Widget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AMenuHUD::ChangeState(EMenuState State)
{
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
