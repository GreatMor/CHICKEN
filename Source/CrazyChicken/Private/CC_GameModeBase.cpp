// Fill out your copyright notice in the Description page of Project Settings.


#include "CC_GameModeBase.h"
#include "Player/BasePlayer.h"
#include "BasePlayerController.h"

ACC_GameModeBase::ACC_GameModeBase()
{
    DefaultPawnClass = ABasePlayer::StaticClass();
    PlayerControllerClass = ABasePlayerController::StaticClass();
}
