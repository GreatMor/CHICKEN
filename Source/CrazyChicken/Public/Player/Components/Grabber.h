// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Engine/Classes/Components/InputComponent.h"
#include "Grabber.generated.h"

class ABasePlayer;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CRAZYCHICKEN_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:
	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	
	AActor* GrabActor;

	float Reach = 50.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	UPROPERTY()
	USkeletalMeshComponent* PlayerSkeletal;

	void Grab();

	void Release();
	//������� ���������� �����	
	void FindPhysicsHandleComponent();

	//������������� ������� ��������� 
	void SetupInputComponent();

	//���������� ���� ��� ������������� ��� ������� ��� ���� � ������������
	const FHitResult GetFirstPhysicsBodyInReach();

	FVector GetReachLineStart();//���������� ������� ������ ����� ������������
	FVector GetReachLineEnd();//���������� ������� ����� ����� ������������

public:

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
