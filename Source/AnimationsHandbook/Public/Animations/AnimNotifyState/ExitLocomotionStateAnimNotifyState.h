// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ExitLocomotionStateAnimNotifyState.generated.h"

/**
 * Notify state used with locomotion sequences to determine when we can start transitioning out of the locomotion state
 */
UCLASS()
class ANIMATIONSHANDBOOK_API UExitLocomotionStateAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
};
