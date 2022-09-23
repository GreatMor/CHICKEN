// Fill out your copyright notice in the Description page of Project Settings.


#include "HostileEnvironment/RawMaterial.h"

// Sets default values
ARawMaterial::ARawMaterial()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ARawMaterial::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("MaxTimeBunfier %f =   Weight = %f   SpawnChance = %f "), MaxTimeBunfier, Weight, SpawnChance)
}

// Called every frame
void ARawMaterial::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

