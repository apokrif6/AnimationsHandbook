﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimationsHandbookAnimInstance.generated.h"

enum class EGait : uint8;
struct FLocomotionDirectionThresholds;
enum class ELocomotionDirection : uint8;
/**
 * 
 */
UCLASS()
class ANIMATIONSHANDBOOK_API UAnimationsHandbookAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	ELocomotionDirection CalculateLocomotionDirection(const float InLocomotionAngle,
	                                                  const ELocomotionDirection InLocomotionDirection) const;

	UFUNCTION(BlueprintCallable, meta=(BlueprintThreadSafe))
	EGait GetCurrentGait() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float Speed = ForceInit;

	//TODO
	//move this data to locomotion cycle specific structure
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float LocomotionAngle = ForceInit;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	ELocomotionDirection LocomotionDirection;

	UPROPERTY(BlueprintReadOnly, Category = "Movement|Yaw")
	float CurrentYaw = ForceInit;

	UPROPERTY(BlueprintReadOnly, Category = "Movement|Yaw")
	float PreviousYaw = ForceInit;

	UPROPERTY(BlueprintReadOnly, Category = "Movement|Yaw")
	float YawDelta = ForceInit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Yaw")
	float YawInterpolationSpeed = 4.f;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float LeanAngle = ForceInit;

	UPROPERTY(BlueprintReadOnly, Category = "Movement|Acceleration")
	bool bIsAccelerating = false;

	UPROPERTY(BlueprintReadOnly, Category = "Movement|Acceleration")
	FVector PreviousVelocity2D{};

	UPROPERTY(BlueprintReadOnly, Category = "Movement|Acceleration")
	FVector Velocity2D{};

	UPROPERTY(BlueprintReadOnly, Category = "Movement|Acceleration")
	FVector Acceleration2D{};

	UPROPERTY(BlueprintReadOnly, Category = "Movement|Acceleration")
	FVector RelativeAcceleration{};

private:
	UPROPERTY()
	TObjectPtr<ACharacter> OwnerCharacter;
};
