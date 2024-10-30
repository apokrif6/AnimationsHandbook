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

USTRUCT(BlueprintType)
struct FLocomotionDirectionThresholds
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion Direction")
	FFloatInterval Forward{0.f, 0.f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion Direction")
	FFloatInterval Backward{0.f, 0.f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion Direction")
	float Deadzone = ForceInit;
};
