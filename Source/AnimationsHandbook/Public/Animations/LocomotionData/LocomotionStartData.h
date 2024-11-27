// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LocomotionStartData.generated.h"

USTRUCT(BlueprintType)
struct FLocomotionStartData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float StartDistance = ForceInit;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float StartLocationDelta = ForceInit;
};
