// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/AuthWidget.h"

#include "ShooterGameInstance.h"
#include "Components/Button.h"
#include "Components/CircularThrobber.h"
#include "Components/EditableTextBox.h"
#include "Interfaces/IHttpResponse.h"
#include "Menu/MenuGameMode.h"

DEFINE_LOG_CATEGORY_STATIC(LogAuth, All, All);

UAuthWidget::UAuthWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Http = &FHttpModule::Get();
}

void UAuthWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SignButton->OnClicked.AddDynamic(this, &UAuthWidget::OnSignButtonClicked);
}

void UAuthWidget::OnSignButtonClicked()
{
	auto Login = LoginTextBox->GetText().ToString();
	auto Password = PasswordTextBox->GetText().ToString();

	if (Password.IsEmpty() || Login.IsEmpty())
	{
		UE_LOG(LogAuth, Warning, TEXT("Login or password empty"));
		return;
	}

	auto Request = Http->CreateRequest();

	Request->SetURL("http://localhost:5000/api/auth");
	Request->SetVerb("POST");
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));

	const FString Content = FString::Printf(TEXT("{ \"login\": \"%s\", \"password\": \"%s\" }"), *Login, *Password);
	Request->SetContentAsString(Content);
	Request->OnProcessRequestComplete().BindUObject(this, &UAuthWidget::OnResponse);

	InRequestIndicator->SetVisibility(ESlateVisibility::Visible);
	Request->ProcessRequest();
}

void UAuthWidget::OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool ConnectionSuccessfully)
{
	IsLoading = false;
	TSharedPtr<FJsonObject> JsonObject;
	const auto ResponseBody = Response->GetContentAsString();

	if (Response->GetResponseCode() == 200)
	{
		auto Reader = TJsonReaderFactory<>::Create(ResponseBody);

		if (FJsonSerializer::Deserialize(Reader, JsonObject))
		{
			const auto Token = JsonObject->GetStringField(TEXT("access_token"));
			UShooterGameInstance* GameInstance = Cast<UShooterGameInstance>(GetGameInstance());
			//GameInstance->SetToken(Token);

			const auto GameMode = Cast<AMenuGameMode>(GetWorld()->GetAuthGameMode());
			if (GameMode)
			{
				GameMode->OnUserAuthorized.Broadcast();
			}
			OnAuthorize.Broadcast();
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, *ResponseBody);
	}

	InRequestIndicator->SetVisibility(ESlateVisibility::Visible);
}
