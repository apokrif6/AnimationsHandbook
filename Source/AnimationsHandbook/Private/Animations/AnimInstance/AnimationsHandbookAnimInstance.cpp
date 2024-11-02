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

		LocomotionDirection = CalculateLocomotionDirection(LocomotionAngle, LocomotionDirection);

		//cache yaw, and subtract later
		PreviousYaw = CurrentYaw;

		const FRotator ActorRotation = OwnerCharacter->GetActorRotation();
		CurrentYaw = ActorRotation.Yaw;

		YawDelta = CurrentYaw - PreviousYaw;

		const float InterpolatedYaw = UKismetMathLibrary::SafeDivide(YawDelta, DeltaSeconds) / 4.f;

		LeanAngle = FMath::ClampAngle(InterpolatedYaw, -90.f, 90.f);

		bIsAccelerating = OwnerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Length() > 0.f;
	}
}

ELocomotionDirection UAnimationsHandbookAnimInstance::CalculateLocomotionDirection(
	const float InLocomotionAngle, const ELocomotionDirection InLocomotionDirection) const
{
	const auto [Forward, Backward, Deadzone] = OwnerCharacter->GetCharacterMovement<
		UAnimationsHandbookCharacterMovementComponent>()->GetLocomotionDirectionThresholds();

	switch (InLocomotionDirection)
	{
	case ELocomotionDirection::Forward:
		if (InLocomotionAngle >= Forward.Min - Deadzone && InLocomotionAngle <= Forward.Max + Deadzone)
		{
			return ELocomotionDirection::Forward;
		}
	case ELocomotionDirection::Backward:
		if (!(InLocomotionAngle >= Backward.Min + Deadzone && InLocomotionAngle <= Backward.Max - Deadzone))
		{
			return ELocomotionDirection::Backward;
		}
	case ELocomotionDirection::Left:
		if (InLocomotionAngle >= Forward.Min + Deadzone && InLocomotionAngle <= Backward.Min - Deadzone)
		{
			return ELocomotionDirection::Left;
		}
	case ELocomotionDirection::Right:
		if (InLocomotionAngle >= Forward.Max - Deadzone && InLocomotionAngle <= Backward.Max + Deadzone)

		{
			return ELocomotionDirection::Right;
		}
	}

	if (!(InLocomotionAngle >= Backward.Min && InLocomotionAngle <= Backward.Max))
	{
		return ELocomotionDirection::Backward;
	}

	if (InLocomotionAngle >= Forward.Min && InLocomotionAngle <= Forward.Max)
	{
		return ELocomotionDirection::Forward;
	}

	return InLocomotionAngle < 0 ? ELocomotionDirection::Left : ELocomotionDirection::Right;
}

EGait UAnimationsHandbookAnimInstance::GetCurrentGait() const
{
	return OwnerCharacter->GetCharacterMovement<UAnimationsHandbookCharacterMovementComponent>()->GetCurrentGait();
}
