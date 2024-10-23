// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimationsHandbook/Public/Animations/AnimInstance/AnimationsHandbookAnimInstance.h"
#include "KismetAnimationLibrary.h"
#include "Animations/Types/LocomotionDirection.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Movement/AnimationsHandbookCharacterMovementComponent.h"

void UAnimationsHandbookAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UAnimationsHandbookAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (ensure(OwnerCharacter))
	{
		FVector HorizontalVelocity = OwnerCharacter->GetVelocity();
		HorizontalVelocity.Z = 0.f;
		Speed = HorizontalVelocity.Size();

		LocomotionAngle = UKismetAnimationLibrary::CalculateDirection(HorizontalVelocity,
		                                                              OwnerCharacter->GetActorRotation());

		//TODO
		//move this to developer settings!
		FLocomotionDirectionThresholds LocomotionDirectionThresholds;
		LocomotionDirectionThresholds.Forward = {-50.f, 50.f};
		LocomotionDirectionThresholds.Backward = {-130.f, 130.f};
		LocomotionDirectionThresholds.Deadzone = 20.f;
		LocomotionDirection = CalculateLocomotionDirection(LocomotionAngle, LocomotionDirection,
		                                                   LocomotionDirectionThresholds);

		const FRotator AimRotation = OwnerCharacter->GetBaseAimRotation();
		const FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(OwnerCharacter->GetVelocity());

		OffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

		bIsAccelerating = OwnerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Length() > 0.f;
	}
}

ELocomotionDirection UAnimationsHandbookAnimInstance::CalculateLocomotionDirection(
	const float InLocomotionAngle, const ELocomotionDirection InLocomotionDirection,
	const FLocomotionDirectionThresholds& LocomotionDirectionThresholds)
{
	switch (InLocomotionDirection)
	{
	case ELocomotionDirection::Forward:
		if (InLocomotionAngle >= LocomotionDirectionThresholds.Forward.Min - LocomotionDirectionThresholds.Deadzone &&
			InLocomotionAngle <= LocomotionDirectionThresholds.Forward.Max + LocomotionDirectionThresholds.Deadzone)
		{
			return ELocomotionDirection::Forward;
		}
	case ELocomotionDirection::Backward:
		if (!(InLocomotionAngle >= LocomotionDirectionThresholds.Backward.Min + LocomotionDirectionThresholds.Deadzone
			&&
			InLocomotionAngle <= LocomotionDirectionThresholds.Backward.Max - LocomotionDirectionThresholds.Deadzone))
		{
			return ELocomotionDirection::Backward;
		}
	case ELocomotionDirection::Left:
		if (InLocomotionAngle >= LocomotionDirectionThresholds.Forward.Min + LocomotionDirectionThresholds.Deadzone &&
			InLocomotionAngle <= LocomotionDirectionThresholds.Backward.Min - LocomotionDirectionThresholds.Deadzone)
		{
			return ELocomotionDirection::Left;
		}
	case ELocomotionDirection::Right:
		if (InLocomotionAngle >= LocomotionDirectionThresholds.Forward.Max - LocomotionDirectionThresholds.Deadzone &&
			InLocomotionAngle <= LocomotionDirectionThresholds.Backward.Max + LocomotionDirectionThresholds.Deadzone)

		{
			return ELocomotionDirection::Right;
		}
	}

	if (!(InLocomotionAngle >= LocomotionDirectionThresholds.Backward.Min && InLocomotionAngle <=
		LocomotionDirectionThresholds.Backward.Max))
	{
		return ELocomotionDirection::Backward;
	}

	if (InLocomotionAngle >= LocomotionDirectionThresholds.Forward.Min && InLocomotionAngle <=
		LocomotionDirectionThresholds.Forward.Max)
	{
		return ELocomotionDirection::Forward;
	}

	return InLocomotionAngle < 0 ? ELocomotionDirection::Left : ELocomotionDirection::Right;
}

EGait UAnimationsHandbookAnimInstance::GetCurrentGait() const
{
	return OwnerCharacter->GetCharacterMovement<UAnimationsHandbookCharacterMovementComponent>()->GetCurrentGait();
}
