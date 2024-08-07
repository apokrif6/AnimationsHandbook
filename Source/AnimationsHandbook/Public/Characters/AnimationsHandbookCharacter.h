// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AnimationsHandbookCharacter.generated.h"

UCLASS()
class ANIMATIONSHANDBOOK_API AAnimationsHandbookCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAnimationsHandbookCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
