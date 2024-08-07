// Fill out your copyright notice in the Description page of Project Settings.

#include "AnimationsHandbook/Public/Animations/AnimInstance/AnimationsHandbookAnimInstance.h"
#include "GameFramework/Character.h"

void UAnimationsHandbookAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (ensure(OwnerCharacter))
	{
		FVector HorizontalVelocity = OwnerCharacter->GetVelocity();
		HorizontalVelocity.Z = 0.f;
		Speed = HorizontalVelocity.Size();
	}
}

void UAnimationsHandbookAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}
