// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bonfire.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class ABasePlayer;
class UHealthComponent;

UCLASS()
class CRAZYCHICKEN_API ABonfire : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Components", meta = (ClampMax = "1000", ClampMin = "0"))
	float MaxBurningTime = 10.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyBonfire = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radius = 3000;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor SphereColor = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHeatRecovery = 110.f;

private:

	float CurrentHeatRecovery = 10.f;
	float CurrentBurningTime = 10.f;	

	UPROPERTY()
	ABasePlayer* OverlapPlayer = nullptr;
	
public:	
	// Sets default values for this actor's properties
	ABonfire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool IsBurning();
	float CalculetRadius();
};
