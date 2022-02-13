// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/CorePlayerController.h"

#include "Menu/MenuGameMode.h"

DEFINE_LOG_CATEGORY_STATIC(LogCorePlayerController, All, All);

void ACorePlayerController::BeginPlay()
{
	const auto GameMode = Cast<AMenuGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->OnUserAuthorized.AddDynamic(this, &ACorePlayerController::OnAuthorized);
	}
}

void ACorePlayerController::LoadPlayer()
{
	if (!Http)
		Http = &FHttpModule::Get();

	auto Request = Http->CreateRequest();

	Request->SetURL("http://localhost:5000/api/storage/d3176b73-6223-481f-a560-81549cc579df/items");
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetHeader(TEXT("Accepts"), TEXT("application/json"));

	Request->OnProcessRequestComplete().BindUObject(this, &ACorePlayerController::OnItemsResponse);
	Request->ProcessRequest();
}

void ACorePlayerController::OnAuthorized()
{
	LoadPlayer();
}


void ACorePlayerController::OnItemsResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool ConnectionSuccessfully)
{
	if (ConnectionSuccessfully && Response->GetResponseCode() == 200)
	{
		FString Body = Response->GetContentAsString();
		UE_LOG(LogCorePlayerController, Display, TEXT("%s"), *Body);

		TSharedPtr<FJsonValue> Json;
		auto Reader = TJsonReaderFactory<>::Create(Body);
		if (FJsonSerializer::Deserialize(Reader, Json))
		{
			auto ItemsJson = Json->AsArray();
			for (const auto ItemJson : ItemsJson)
			{
				const auto ItemObjectJson = ItemJson->AsObject();
				const auto PosJson = ItemObjectJson->GetObjectField("pos");
				const auto InstanceJson = ItemObjectJson->GetObjectField("instance");
				
				FStorageItem Item;
				Item.Pos.X = PosJson->GetNumberField("x");
				Item.Pos.Y = PosJson->GetNumberField("y");

				UItemInstance* ItemInstance = NewObject<UItemInstance>();
				FGuid::Parse(InstanceJson->GetStringField("id"), ItemInstance->Id);
				ItemInstance->ItemId = FName(InstanceJson->GetStringField("itemId"));
				
				Item.Instance = ItemInstance;

				MainStorageItems.Add(Item);
				UE_LOG(LogCorePlayerController, Display, TEXT("ITEM X:%d Y:%d ItemId:%s"), Item.Pos.X, Item.Pos.Y, *ItemInstance->ItemId.ToString());
			}
		}

		OnLoadFinished.Broadcast();
	}
	else
	{
		UE_LOG(LogCorePlayerController, Error, TEXT("Error while accept items"));
	}
}
