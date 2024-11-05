// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animations/LocomotionData/LocomotionCycleData.h"
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

protected:
	//TODO
	//move this data to locomotion cycle specific structure

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Yaw")
	float YawInterpolationSpeed = 4.f;

	UPROPERTY(BlueprintReadOnly, Category = "Movement|Acceleration")
	bool bIsAccelerating = false;

	UPROPERTY(BlueprintReadOnly, Category = "Movement|Locomotion")
	FLocomotionCycleData LocomotionCycleData{};

private:
	UPROPERTY()
	TObjectPtr<ACharacter> OwnerCharacter;

	float CurrentYaw = ForceInit;

	float PreviousYaw = ForceInit;

	float YawDelta = ForceInit;

	FVector PreviousVelocity2D{};

	FVector Velocity2D{};

	FVector Acceleration2D{};
};
