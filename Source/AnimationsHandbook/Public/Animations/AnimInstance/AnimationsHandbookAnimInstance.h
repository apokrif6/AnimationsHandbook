// Fill out your copyright notice in the Description page of Project Settings.

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
	                                                  const ELocomotionDirection InLocomotionDirection,
	                                                  const FLocomotionDirectionThresholds&
	                                                  LocomotionDirectionThresholds);

	//TODO
	//replace with interface call/property access
	UFUNCTION(BlueprintCallable, meta=(BlueprintThreadSafe))
	EGait GetCurrentGait() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float Speed = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float LocomotionAngle = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	ELocomotionDirection LocomotionDirection;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float OffsetYaw = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool bIsAccelerating = false;

private:
	UPROPERTY()
	TObjectPtr<ACharacter> OwnerCharacter;
};
