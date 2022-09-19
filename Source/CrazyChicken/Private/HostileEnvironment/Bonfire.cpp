// Fill out your copyright notice in the Description page of Project Settings.


#include "HostileEnvironment/Bonfire.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Player/Components/HealthComponent.h"
#include "BasePlayer.h"

// Sets default values
ABonfire::ABonfire()
{
	BodyBonfire = CreateDefaultSubobject<UStaticMeshComponent>("BodyBonfire");
	RootComponent = BodyBonfire;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetSphereRadius(Radius);
	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SphereComponent->bHiddenInGame = false;
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABonfire::BeginPlay()
{
	Super::BeginPlay();	

	CurrentBurningTime = MaxBurningTime;
	CurrentHeatRecovery = MaxHeatRecovery;
}

// Called every frame
void ABonfire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsBurning())
	{
		CurrentBurningTime = CurrentBurningTime - DeltaTime;
	}
	else
	{
		this->Destroy();
	}
}

bool ABonfire::IsBurning()
{ 	
	return CurrentBurningTime <= 0 ? false : true;
}

float ABonfire::CalculetRadius()
{
	return 0.f;
}

