// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StorageComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnItemsChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAME_API UStorageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStorageComponent();

protected:
	virtual void BeginPlay() override;
	
public:
	UFUNCTION(BlueprintCallable)
	void AddItem(class UItemInstance* ItemInstance);

	UFUNCTION(BlueprintCallable)
	void RemoveItem(class UItemInstance* ItemInstance);

	UFUNCTION(BlueprintCallable)
	TArray<class UItemInstance*> GetItems() const { return Items; }

	FOnItemsChanged OnItemsChanged;
private:
	TArray<class UItemInstance*> Items;
};
