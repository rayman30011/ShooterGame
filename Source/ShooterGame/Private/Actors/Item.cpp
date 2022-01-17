// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Item.h"

#include "Structs.h"
#include "Components/StorageComponent.h"
#include "Engine/DataTable.h"

DEFINE_LOG_CATEGORY_STATIC(LogItem, All, All);

AItem::AItem()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	PrimaryActorTick.bCanEverTick = false;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	const auto ItemInfo = ItemDataTable->FindRow<FItemInfo>(ItemKey, TEXT("Storage Component"));
	if (ItemInfo)
	{
		ItemInstance = NewObject<UItemInstance>();
		ItemInstance->ItemId = ItemKey;
		ItemInstance->ItemType = ItemInfo->ItemType;
	}
	else
	{
		UE_LOG(LogItem, Error, TEXT("Not found Item [%s]"), *ItemKey.ToString());
	}
}

void AItem::Interact_Implementation(AActor* Initiator)
{
	if (!Initiator) return;

	const auto Storage = Cast<UStorageComponent>(Initiator->GetComponentByClass(UStorageComponent::StaticClass()));
	Storage->AddItem(ItemInstance);
	
	Destroy();
}

