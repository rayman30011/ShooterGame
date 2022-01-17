// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StorageComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogStorageComponent, All, All);

UStorageComponent::UStorageComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UStorageComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UStorageComponent::AddItem(UItemInstance* ItemInstance)
{
	Items.Add(ItemInstance);
	UE_LOG(LogStorageComponent, Display, TEXT("Item Added"));
	OnItemsChanged.Broadcast();
}

void UStorageComponent::RemoveItem(UItemInstance* ItemInstance)
{
	Items.Remove(ItemInstance);
	UE_LOG(LogStorageComponent, Display, TEXT("Item Removed"));
	OnItemsChanged.Broadcast();
}

