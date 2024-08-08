// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationsHandbook/Public/Characters/AnimationsHandbookCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

AAnimationsHandbookCharacter::AAnimationsHandbookCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator{0.f, 540.f, 0.f};
}

void AAnimationsHandbookCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAnimationsHandbookCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
