﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animations/Types/LocomotionDirection.h"
#include "LocomotionCycleData.generated.h"

enum class ELocomotionDirection : uint8;

/**
 * Struct to pass necessary locomotion cycle data to editable and exposed anim nodes
 */
USTRUCT(BlueprintType)
struct FLocomotionCycleData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	ELocomotionDirection PreviousLocomotionDirection = ELocomotionDirection::Forward;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	ELocomotionDirection LocomotionDirection = ELocomotionDirection::Forward;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	ELocomotionDirection AccelerationLocomotionDirection = ELocomotionDirection::Forward;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector Velocity{};

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector Velocity2D{};

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	FVector RelativeAcceleration{};

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bGaitChanged = false;
};
