// Fill out your copyright notice in the Description page of Project Settings.


#include "Movement/AnimationsHandbookCharacterMovementComponent.h"
#include "Log/AnimationHandbookCharacterLog.h"

UAnimationsHandbookCharacterMovementComponent::UAnimationsHandbookCharacterMovementComponent()
{
}

void UAnimationsHandbookCharacterMovementComponent::UpdateGait(const EGait DesiredGait)
{
	CurrentGait = DesiredGait;

	const FGaitSettings* SettingsForDesiredGait = GaitSettings.Find(CurrentGait);
	if (!SettingsForDesiredGait)
	{
		UE_LOG(AHMovementLog, Warning,
		       TEXT("UAnimationsHandbookCharacterMovementComponent can't find settings for %s %s gait"),
		       *GetOwner()->GetName(), *UEnum::GetValueAsString(DesiredGait));
		return;
	}

	MaxWalkSpeed = SettingsForDesiredGait->MaxSpeed;
	MaxAcceleration = SettingsForDesiredGait->MaxAcceleration;
	BrakingDecelerationWalking = SettingsForDesiredGait->BrakingDeceleration;
	BrakingFrictionFactor = SettingsForDesiredGait->BrakingFrictionFactor;
	bUseSeparateBrakingFriction = SettingsForDesiredGait->bUseSeparateBrakingFriction;
	BrakingFriction = SettingsForDesiredGait->BrakingFriction;
}

void UAnimationsHandbookCharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	UpdateGait(EGait::Walking);
}
