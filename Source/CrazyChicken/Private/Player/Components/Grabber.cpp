// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Grabber.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/Controller.h"
#include "Engine/Classes/PhysicsEngine/PhysicsHandleComponent.h"
#include "Engine/Public/DrawDebugHelpers.h"
#include "Player/BasePlayer.h"
#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();

	SetupInputComponent();

	TArray<UActorComponent*> Components;
	GetOwner()->GetComponents(Components);
	
	for (int i = 0; i < Components.Num(); i++)
	{
		PlayerSkeletal = Cast<USkeletalMeshComponent>(Components[i]);
		if (PlayerSkeletal)
			break;
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}	
}

void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle) { return; }
	if (PhysicsHandle)
	{
		PhysicsHandle->bInterpolateTarget = 0;
		UE_LOG(LogTemp, Warning, TEXT("FindPhysicsComponent = true"));
	}

}

void UGrabber::Grab()
{	
	auto HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	GrabActor = HitResult.GetActor();
	//auto ActorHit = HitResult.GetActor();
	/*UWorld* World = this->GetOwner()->GetWorld();
	DrawDebugLine
	(
		World,
		GetReachLineStart(),
		GetReachLineEnd(),
		FColor::Red,
		false,
		10,
		2.f,
		2.f
	);*/
	//if (ActorHit)
	//{
	//	ABasePlayer* Player = Cast<ABasePlayer>(GetOwner());
	//	if (!PhysicsHandle)
	//	{			
	//		if(Player)
	//			Player->SetGrab(false);
	//		 return;
	//	}

	//	PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab,
	//		NAME_None, //êîñòè íå íóæíû
	//		ComponentToGrab->GetOwner()->GetActorLocation(),
	//		FRotator(0, 0, 0));

	//	if (Player)
	//		Player->SetGrab(true);
	//	UE_LOG(LogTemp, Warning, TEXT("location : %s "), *ComponentToGrab->GetOwner()->GetActorLocation().ToString())

	//}
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (GrabActor)
	{
		GrabActor->SetActorLocation(GetReachLineEnd());
		FVector PlayerViwePointLocation;
		FRotator PlayerViwePointRotation;

		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
			OUT PlayerViwePointLocation,
			OUT PlayerViwePointRotation);
		GrabActor->SetActorRotation(PlayerViwePointRotation);
	}
	/*GetReachLineEnd();
	PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	PhysicsHandle->SetTargetRotation(this->GetOwner()->GetActorRotation());*/
}

void UGrabber::Release()
{
	//PhysicsHandle->ReleaseComponent();
	if (GrabActor)
	{
		GrabActor = nullptr;
	}
	ABasePlayer* Player = Cast<ABasePlayer>(GetOwner());
	if (Player)
		Player->SetGrab(false);

}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FCollisionQueryParams TraceParametrs(FName(TEXT("")), false, GetOwner());
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType
	(
		OUT HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParametrs
	);

	AActor* ActorHit = HitResult.GetActor(); 
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor hit : %s "), *(ActorHit->GetName()));
	}

	return HitResult;
}

FVector UGrabber::GetReachLineStart()
{
	FVector StartLineTrace(0);

	if(PlayerSkeletal)
		StartLineTrace = PlayerSkeletal->GetSocketLocation("StartLineTrace");
	
	return StartLineTrace;
}

FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerViwePointLocation;
	FRotator PlayerViwePointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViwePointLocation,
		OUT PlayerViwePointRotation);

	FVector LintraceEnd = GetReachLineStart() + (PlayerViwePointRotation.Vector() * Reach);
	return LintraceEnd;
}

