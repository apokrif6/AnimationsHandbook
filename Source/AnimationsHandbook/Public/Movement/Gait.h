// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Gait.generated.h"

UENUM(Blueprintable)
enum class EGait : uint8
{
	Walking,
	Running
};

USTRUCT(BlueprintType)
struct FGaitSettings
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Settings")
	float MaxSpeed = ForceInit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Settings")
	float MaxAcceleration = ForceInit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Settings")
	float BrakingDeceleration = ForceInit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Settings")
	float BrakingFrictionFactor = ForceInit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Settings")
	bool bUseSeparateBrakingFriction = ForceInit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement Settings")
	float BrakingFriction = ForceInit;
};
