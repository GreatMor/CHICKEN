// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ShuterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYCHICKEN_API UShuterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
    virtual float GetMaxSpeed() const override;
private:
    UPROPERTY(EditAnywhere, Category = "Movemrnt", meta = (ClampMin = "1.5", ClampMax = "4"))
    float RunModifier = 2;
};
