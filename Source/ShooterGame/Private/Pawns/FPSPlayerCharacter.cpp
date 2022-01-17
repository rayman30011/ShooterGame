// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGame/Public/Pawns/FPSPlayerCharacter.h"

#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "Interfaces/Interactable.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPSCharacter, All, All);

AFPSPlayerCharacter::AFPSPlayerCharacter() : Super()
{
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(GetMesh(), "spine_03");
}

void AFPSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AFPSPlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &AFPSPlayerCharacter::LookRight);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFPSPlayerCharacter::Interact);
}

void AFPSPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(DefaultLocomotionAsset);
}

void AFPSPlayerCharacter::Interact()
{
	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + Camera->GetForwardVector() * 200;

	const auto Shape = FCollisionShape::MakeBox(FVector(200, 20, 20));
	const auto Rot = Camera->GetComponentRotation().Quaternion();
	
	FHitResult Result;
	GetWorld()->SweepSingleByChannel(Result, Start, End, Rot, ECC_Visibility, Shape);
	
	if (!Result.bBlockingHit) return;
	if (!Result.GetActor()) return;
	
	if (!Result.GetActor()->Implements<UInteractable>()) return;

	IInteractable::Execute_Interact(Result.GetActor(), this);
}

void AFPSPlayerCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AFPSPlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AFPSPlayerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(-Value);
}

void AFPSPlayerCharacter::LookRight(float Value)
{
	AddControllerYawInput(Value);
}
