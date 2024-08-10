// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimationsHandbook/Public/Animations/AnimInstance/AnimationsHandbookAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

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

		const FRotator AimRotation = OwnerCharacter->GetBaseAimRotation();
		const FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(OwnerCharacter->GetVelocity());

		OffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

		bIsAccelerating = OwnerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Length() > 0.f;
	}
}
