// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimationsHandbook/Public/Characters/AnimationsHandbookCharacter.h"

AAnimationsHandbookCharacter::AAnimationsHandbookCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAnimationsHandbookCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAnimationsHandbookCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
