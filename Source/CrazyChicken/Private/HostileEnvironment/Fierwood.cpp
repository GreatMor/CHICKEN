 //Fill out your copyright notice in the Description page of Project Settings.


#include "HostileEnvironment/Fierwood.h"

AFierwood::AFierwood()
{
	PrimaryActorTick.bCanEverTick = true;
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Body"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshBodyAsset(TEXT("StaticMesh'/Game/Environment/Meshes/ActiveProps/SM_Tree_Fallen_01.SM_Tree_Fallen_01'"));
	if (MeshBodyAsset.Succeeded())
	{
		PrimaryActorTick.bCanEverTick = true;

		this->ShouldTickIfViewportsOnly();
		//Body->SetNotifyRigidBodyCollision(true);
		Body->SetStaticMesh(MeshBodyAsset.Object);
		/*Body->SetRelativeLocation(this->GetActorLocation());
		Body->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
		Body->SetWorldScale3D(FVector(1));*/
		SetRootComponent(Body);
	}
	MaxTimeBunfier = 5;
	Weight = 0.5;
	SpawnChance = 0.8;
}
