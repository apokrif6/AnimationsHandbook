// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animations/LocomotionData/LocomotionCycleData.h"
#include "Animations/LocomotionData/LocomotionSharedData.h"
#include "Animations/LocomotionData/LocomotionStartData.h"
#include "AnimationsHandbookAnimInstance.generated.h"

class UAnimationsHandbookCharacterMovementComponent;
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

	UFUNCTION(BlueprintCallable, meta=(BlueprintThreadSafe))
	UAnimationsHandbookCharacterMovementComponent* GetCharacterMovementComponent() const;

	ELocomotionDirection CalculateLocomotionDirection(const float InLocomotionAngle,
	                                                  const ELocomotionDirection InLocomotionDirection) const;
#pragma region StartState
	UFUNCTION(BlueprintCallable, meta=(BlueprintThreadSafe))
	void SetupStartState_Internal();

	UFUNCTION(BlueprintCallable, meta=(BlueprintThreadSafe))
	void UpdateStartState_Internal();
#pragma endregion StartState

protected:
	//TODO
	//move this data to locomotion cycle specific structure

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Yaw")
	float YawInterpolationSpeed = 4.f;

	UPROPERTY(BlueprintReadOnly, Category = "Movement|Acceleration")
	bool bIsAccelerating = false;

	UPROPERTY(BlueprintReadOnly, Category = "Movement|Locomotion")
	FLocomotionSharedData LocomotionSharedData{};

	UPROPERTY(BlueprintReadOnly, Category = "Movement|Locomotion")
	FLocomotionStartData LocomotionStartData{};

	UPROPERTY(BlueprintReadOnly, Category = "Movement|Locomotion")
	FLocomotionCycleData LocomotionCycleData{};

private:
	UPROPERTY()
	TObjectPtr<ACharacter> OwnerCharacter;

	float CurrentYaw = ForceInit;

	float PreviousYaw = ForceInit;

	float YawDelta = ForceInit;

	FVector PreviousVelocity2D{};

	FVector Acceleration2D{};

	FVector Location{};

	FVector PreviousLocation{};

	float LocationDelta = ForceInit;
};
