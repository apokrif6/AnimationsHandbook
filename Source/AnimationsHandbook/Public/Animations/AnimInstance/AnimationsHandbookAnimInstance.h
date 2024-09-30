// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimationsHandbookAnimInstance.generated.h"

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

private:
	UPROPERTY()
	ACharacter* OwnerCharacter;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement", meta=(AllowPrivateAccess = "true"))
	float Speed = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement", meta=(AllowPrivateAccess = "true"))
	float LocomotionAngle = 0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement", meta=(AllowPrivateAccess = "true"))
	float OffsetYaw = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement", meta=(AllowPrivateAccess = "true"))
	bool bIsAccelerating = false;
};
