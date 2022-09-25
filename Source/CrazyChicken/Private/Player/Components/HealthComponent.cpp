// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/HealthComponent.h"
//#include "Dev/IceDamageType.h"
//#include "Dev/FireDamageType.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "CrazyChicken/Public/HostileEnvironment/Bonfire.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}
// Called when the game starts
void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    Health = MaxHealth;
    OnHealthChange.Broadcast(Health);

    AActor* ComponentOwner = GetOwner();
    if(ComponentOwner)
    {
       ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamageHandle);
       ComponentOwner->OnActorBeginOverlap.AddDynamic(this, &UHealthComponent::OnOverlapActivateSphere);
       ComponentOwner->OnActorEndOverlap.AddDynamic(this, &UHealthComponent::OnOverlapEndActivateSphere);
    }
}

void UHealthComponent::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
                                                    class AController* InstigatedBy, AActor* DamageCauser )
{
    if (Damage <= 0 || IsDeath() || !GetWorld()) return;

    Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth );

    GetWorld()->GetTimerManager().ClearTimer(HealthTimerHandle);
    //OnHealthChange.Broadcast(Health);
     
    if(IsDeath())
    {
      OnDeath.Broadcast();
    }
    else if(AutoHealth && GetWorld())
    {
      GetWorld()->GetTimerManager().SetTimer(HealthTimerHandle, this,&UHealthComponent::HealthUpdate, HealtUpdateTiame,true, HealtDelay);
    }
}

void UHealthComponent::HealthUpdate()
{    
    Health = FMath::Min(Health+HealthModifier, MaxHealth);
    //OnHealthChange.Broadcast(Health);  
    
    if(Health == MaxHealth && GetWorld())
    {
      GetWorld()->GetTimerManager().ClearTimer(HealthTimerHandle);
    }
}

void UHealthComponent::OnOverlapActivateSphere(AActor* MyOverlappedActor, AActor* OtherActor)
{
    ABonfire* OverlapActor = Cast<ABonfire>(OtherActor);
    if(OverlapActor)
    {
        if(!OverlapActor->IsBurning())
            return;

        GetWorld()->GetTimerManager().ClearTimer(HealthTimerHandle);
        AutoHealth = true;
        GetWorld()->GetTimerManager().SetTimer(HealthTimerHandle, this, &UHealthComponent::HealthUpdate, HealtUpdateTiame, true, 0);
    }
}

void UHealthComponent::TakeDamageCold()
{
    if (ColdDamage <= 0 || IsDeath() || !GetWorld()) return;

    Health = FMath::Clamp(Health - ColdDamage, MinHealth, MaxHealth);
    OnHealthChange.Broadcast(Health);

    if (IsDeath())
    {
        OnDeath.Broadcast();
    }
}

void UHealthComponent::OnOverlapEndActivateSphere(AActor* OverlappedActor, AActor* OtherActor)
{
    AActor* ComponentOwner = GetOwner();
    GetWorld()->GetTimerManager().ClearTimer(HealthTimerHandle);
    if (ComponentOwner)
    {
        AutoHealth = false;
        GetWorld()->GetTimerManager().SetTimer(HealthTimerHandle, this, &UHealthComponent::TakeDamageCold, HealtUpdateTiame, true, 0);
    }
}