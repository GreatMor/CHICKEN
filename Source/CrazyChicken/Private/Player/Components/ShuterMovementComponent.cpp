// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/ShuterMovementComponent.h"
#include "Player/BasePlayer.h"

float UShuterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ABasePlayer*Player = Cast<ABasePlayer>(GetPawnOwner());
    return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
