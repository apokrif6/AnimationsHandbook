// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Movement/Gait.h"
#include "LocomotionSharedData.generated.h"

USTRUCT(BlueprintType)
struct FLocomotionSharedData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Movement|")
	float Speed = ForceInit;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float LocomotionAngle = ForceInit;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float AccelerationLocomotionAngle = ForceInit;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float LeanAngle = ForceInit;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector Acceleration2D{};

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector PivotAcceleration2D{};

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	EGait PreviousGait = EGait::Walking;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	EGait Gait = EGait::Walking;
};
