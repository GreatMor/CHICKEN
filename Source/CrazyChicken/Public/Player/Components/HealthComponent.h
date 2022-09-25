// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChange, float)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRAZYCHICKEN_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UHealthComponent();

    UFUNCTION(BlueprintCallable)
    float GetHealth()const { return Health; };

    UFUNCTION(BlueprintCallable)
    bool IsDeath() const {return Health <= 0.0f;}

    void SetStateRecovery(bool CurrentState){ IsPlayerRecoveryRadius = CurrentState;};

    FOnDeath OnDeath;

    FOnHealthChange OnHealthChange;

    UFUNCTION()
    void OnOverlapActivateSphere(AActor* MyOverlappedActor, AActor* OtherActor);

    UFUNCTION()
    void OnOverlapEndActivateSphere(AActor* OverlappedActor, AActor* OtherActor);


protected:
    // Called when the game starts
    virtual void BeginPlay() override;
   
private:
    UFUNCTION()
    void OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );
   
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMax = "1000", ClampMin = "0"))
    float MaxHealth = 100;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
    bool AutoHealth = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
    float HealtDelay = 3;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
    float HealthModifier = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
    float HealtUpdateTiame = 0.4;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float ColdDamage = 1; 

    void TakeDamageCold();
    
private:

    bool IsPlayerRecoveryRadius = false;

    float Health = 0.f;

    float MinHealth = 0.f;

    FTimerHandle HealthTimerHandle;

    void HealthUpdate();
};
