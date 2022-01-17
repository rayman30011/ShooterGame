// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LocomotionDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API ULocomotionDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UBlendSpace* IdleRun;
};
