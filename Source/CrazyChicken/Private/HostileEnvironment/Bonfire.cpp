// Fill out your copyright notice in the Description page of Project Settings.


#include "HostileEnvironment/Bonfire.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Player/Components/HealthComponent.h"
#include "BasePlayer.h"
#include "HostileEnvironment/Fierwood.h"

// Sets default values
ABonfire::ABonfire()
{
	PrimaryActorTick.bCanEverTick = false;
	BodyBonfire = CreateDefaultSubobject<UStaticMeshComponent>("BodyBonfire");
	RootComponent = BodyBonfire;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetSphereRadius(Radius);
	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SphereComponent->bHiddenInGame = false;

	CollisionActivate = CreateDefaultSubobject<USphereComponent>("CollisionActivate");
	CollisionActivate->SetSphereRadius(100.f);
	CollisionActivate->SetGenerateOverlapEvents(true);
	CollisionActivate->SetupAttachment(RootComponent);
	CollisionActivate->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CollisionActivate->bHiddenInGame = false;
	CollisionActivate->OnComponentBeginOverlap.AddDynamic(this, &ABonfire::ProlongBurning);
}

// Called when the game starts or when spawned
void ABonfire::BeginPlay()
{
	Super::BeginPlay();	

	CurrentBurningTime = MaxBurningTime;
	TimeBurning = MaxTimeBurning;

	if(GetWorld())
		GetWorld()->GetTimerManager().SetTimer(BurningTimerHandle, this, &ABonfire::Burning, 1, true , 0.5f);
}

bool ABonfire::IsBurning()
{ 	
	return CurrentBurningTime <= 0 ? false : true;
}

float ABonfire::CalculetRadius()
{
	return 0.f;
}

void ABonfire::Burning()
{
	if (IsBurning())
	{
		CurrentBurningTime = CurrentBurningTime - 1;
		UE_LOG(LogTemp, Warning, TEXT("current time = %f "), CurrentBurningTime)
	}
	else
	{
		this->Destroy();
		GetWorld()->GetTimerManager().ClearTimer(BurningTimerHandle);
	}
}

void ABonfire::ProlongBurning(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARawMaterial* OwerlapActor = Cast<ARawMaterial>(OtherActor);

	if(OwerlapActor)
	{
		CurrentBurningTime = CurrentBurningTime + OwerlapActor->GetTimeBunfier();
		OwerlapActor->Destroy();
		OwerlapActor = nullptr;
	}
}

