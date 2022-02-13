// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Structs.h"
#include "GameFramework/PlayerController.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Interfaces/IHttpRequest.h"

#include "CorePlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoadFinished);

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API ACorePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	
	void LoadPlayer();

	UPROPERTY(BlueprintAssignable, Category=Events)
	FOnLoadFinished OnLoadFinished;

	UFUNCTION(BlueprintCallable, Category=Storage)
	TArray<FStorageItem> GetItems() const { return MainStorageItems; }
	
protected:
	virtual void BeginPlay() override;
	
private:
	void OnItemsResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool ConnectionSuccessfully);

	UFUNCTION()
	void OnAuthorized();
	
	FHttpModule* Http;
	TArray<FStorageItem> MainStorageItems;
	FStorage MainStorageInfo;
};
