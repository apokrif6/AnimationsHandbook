// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gait.h"
#include "Animations/Types/LocomotionDirection.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AnimationsHandbookCharacterMovementComponent.generated.h"


struct FGaitSettings;
enum class EGait : uint8;

UCLASS(ClassGroup=("Movement"), meta=(BlueprintSpawnableComponent))
class ANIMATIONSHANDBOOK_API UAnimationsHandbookCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UAnimationsHandbookCharacterMovementComponent();

	void UpdateGait(const EGait DesiredGait);

	EGait GetCurrentGait() const { return CurrentGait; }

	FLocomotionDirectionThresholds GetLocomotionDirectionThresholds() const { return LocomotionDirectionThresholds; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
	TMap<EGait, FGaitSettings> GaitSettings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
	FLocomotionDirectionThresholds LocomotionDirectionThresholds;

private:
	EGait CurrentGait = EGait::None;
};
