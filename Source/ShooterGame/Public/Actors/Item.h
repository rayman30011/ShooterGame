// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"

#include "Item.generated.h"

UCLASS()
class SHOOTERGAME_API AItem : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AItem();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ItemKey;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UDataTable* ItemDataTable;
	
	virtual void BeginPlay() override;

public:
	void Interact_Implementation(AActor* Initiator) override;

private:
	class UItemInstance* ItemInstance = nullptr;
};
