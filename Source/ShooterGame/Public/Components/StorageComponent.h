// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StorageComponent.generated.h"


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
	TArray<class UItemInstance*> GetItems() const { return Items; }
private:
	TArray<class UItemInstance*> Items;
};
