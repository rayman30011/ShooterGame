// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Interfaces/IHttpRequest.h"

#include "AuthWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API UAuthWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UAuthWidget(const FObjectInitializer& ObjectInitializer);
protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* SignButton;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* LoginTextBox;

	UPROPERTY(meta = (BindWidget))
	class UEditableTextBox* PasswordTextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsLoading = false;

	virtual void NativeConstruct() override;

private:
	FHttpModule* Http;
	
	UFUNCTION()
	void OnSignButtonClicked();

	void OnResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool ConnectionSuccessfully);
};
