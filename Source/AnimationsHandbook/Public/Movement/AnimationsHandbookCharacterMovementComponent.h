// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gait.h"
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

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gait")
	TMap<EGait, FGaitSettings> GaitSettings;

private:
	EGait CurrentGait = EGait::None;
};
