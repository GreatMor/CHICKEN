// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TypesOfFuel.generated.h"

UENUM()
enum class ETypesFuel : uint8
{

	FierWood	UMETA(DisplayName = "FierWood"),
	Coal 	UMETA(DisplayName = "Coal"),
	Peat		UMETA(DisplayName = "Peat")
};