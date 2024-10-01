// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "LocomotionDirection.generated.h"

UENUM(Blueprintable)
enum class ELocomotionDirection : uint8
{
	Forward,
	Backward,
	Left,
	Right
};

USTRUCT()
struct FLocomotionDirectionThresholds
{
	GENERATED_BODY()

	TInterval<float> Forward;

	TInterval<float> Backward;

	float Deadzone;
};
