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
		LocomotionCycleData.PreviousGait = LocomotionCycleData.Gait;
		LocomotionCycleData.Gait = OwnerCharacter->GetCharacterMovement<UAnimationsHandbookCharacterMovementComponent>()
		                                         ->GetCurrentGait();

		if (LocomotionCycleData.PreviousGait != LocomotionCycleData.Gait)
		{
			LocomotionCycleData.bGaitChanged = true;
		}

		FVector HorizontalVelocity = OwnerCharacter->GetVelocity();
		HorizontalVelocity.Z = 0.f;
		LocomotionCycleData.Speed = HorizontalVelocity.Size();

		LocomotionCycleData.LocomotionAngle = UKismetAnimationLibrary::CalculateDirection(HorizontalVelocity,
			OwnerCharacter->GetActorRotation());

		LocomotionCycleData.PreviousLocomotionDirection = LocomotionCycleData.LocomotionDirection;
		LocomotionCycleData.LocomotionDirection = CalculateLocomotionDirection(
			LocomotionCycleData.LocomotionAngle, LocomotionCycleData.LocomotionDirection);

		PreviousLocation = Location;
		Location = OwnerCharacter->GetActorLocation();

		LocationDelta = (Location - PreviousLocation).Size();

		//cache yaw, and subtract later
		PreviousYaw = CurrentYaw;

		const FRotator ActorRotation = OwnerCharacter->GetActorRotation();
		CurrentYaw = ActorRotation.Yaw;

		YawDelta = CurrentYaw - PreviousYaw;

		const float InterpolatedYaw = UKismetMathLibrary::SafeDivide(YawDelta, DeltaSeconds) / 4.f;

		LocomotionCycleData.LeanAngle = FMath::ClampAngle(InterpolatedYaw, -90.f, 90.f);

		//cache velocity 2d
		PreviousVelocity2D = LocomotionCycleData.Velocity2D;
		LocomotionCycleData.Velocity2D = OwnerCharacter->GetCharacterMovement()->Velocity * FVector{1.f, 1.f, 0};

		Acceleration2D = (LocomotionCycleData.Velocity2D - PreviousVelocity2D) / DeltaSeconds;

		bIsAccelerating = OwnerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Length() > 0.f;

		const float MaxAcceleration = bIsAccelerating
			                              ? OwnerCharacter->GetCharacterMovement()->GetMaxAcceleration()
			                              : OwnerCharacter->GetCharacterMovement()->GetMaxBrakingDeceleration();

		const FVector NormalizedClampedAcceleration2D = Acceleration2D.GetClampedToMaxSize(MaxAcceleration) /
			MaxAcceleration;

		//need be moved to movement component settings
		float GaitAccelerationMultiplier = 0.f;
		switch (LocomotionCycleData.Gait)
		{
		case EGait::Walking:
			GaitAccelerationMultiplier = 0.25f;
			break;
		case EGait::Running:
			GaitAccelerationMultiplier = 0.7f;
			break;
		default: ;
		}

		LocomotionCycleData.RelativeAcceleration = ActorRotation.UnrotateVector(NormalizedClampedAcceleration2D) *
			GaitAccelerationMultiplier;
	}
}

UAnimationsHandbookCharacterMovementComponent* UAnimationsHandbookAnimInstance::GetCharacterMovementComponent() const
{
	if (OwnerCharacter)
	{
		return OwnerCharacter->GetCharacterMovement<UAnimationsHandbookCharacterMovementComponent>();
	}

	return nullptr;
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

void UAnimationsHandbookAnimInstance::SetupStartState_Internal()
{
	LocomotionStartData.StartDistance = 0.f;
}

void UAnimationsHandbookAnimInstance::UpdateStartState_Internal()
{
	LocomotionStartData.StartDistance += LocationDelta;
}
