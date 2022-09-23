#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RawMaterial.generated.h"

UCLASS()
class CRAZYCHICKEN_API ARawMaterial : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARawMaterial();

	float GetTimeBunfier() {return MaxTimeBunfier;};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Body;

	UPROPERTY()
	float MaxTimeBunfier = 5;

	UPROPERTY()
	float Weight = 1;

	UPROPERTY()
	float SpawnChance = 1;
};
