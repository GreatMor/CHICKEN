// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bonfire.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class ABasePlayer;
class UHealthComponent;
class ARawMaterial; 

UCLASS()
class CRAZYCHICKEN_API ABonfire : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMax = "1000", ClampMin = "0"))
	float MaxBurningTime = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float Radius = 300;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyBonfire = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* SM_Fierwood = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* SM_Ash = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* CollisionActivate;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor SphereColor = FColor::Red;

private:

	float TimeBurning = 100.f;
	UPROPERTY()
	float CurrentBurningTime = 10.f;	
	UPROPERTY()
	FTimerHandle BurningTimerHandle;

	UPROPERTY()
	ABasePlayer* OverlapPlayer = nullptr;
	
public:	
	// Sets default values for this actor's properties
	ABonfire();

	UFUNCTION(BlueprintCallable)
	float GetCurrentTimeBurning() const { return CurrentBurningTime; }

	bool IsBurning();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	float CalculetRadius();
	void Burning();

	UFUNCTION()
	void ProlongBurning(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
