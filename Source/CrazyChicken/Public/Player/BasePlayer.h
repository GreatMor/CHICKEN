// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasePlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHealthComponent;
//class UTextRenderComponent;

UCLASS()
class CRAZYCHICKEN_API ABasePlayer : public ACharacter
{
    GENERATED_BODY()

public:
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    ABasePlayer(const FObjectInitializer& ObjInit);

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection();

    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsRunning() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool GetGrab() const { return IsGrab;} ;

    UFUNCTION(BlueprintCallable, Category = "Health")
    UHealthComponent* GetHealthComponent();

    void SetGrab(bool InGrab) { IsGrab = InGrab; }

private:
    void MoveForward(float Amount);
    void MoveRight(float Amount);
    void OnStartRunning();
    void OnStopRunning();
    void OnDeath();
    void OnHealthChange(float Healt);

protected:

    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UHealthComponent* HealthComponent;

    /*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* HealthTextRender;*/

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* AnimDeath;

private:
    bool IsMovingForward = false;
    bool WentsToRun = false;
    bool IsGrab = false;
};
