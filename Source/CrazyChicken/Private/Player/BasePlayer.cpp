// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/BasePlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/Components/ShuterMovementComponent.h"
#include "Player/Components/HealthComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
ABasePlayer::ABasePlayer(const FObjectInitializer& ObjInit) :Super(ObjInit.SetDefaultSubobjectClass<UShuterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArmComponent->SetupAttachment(RootComponent);
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
    HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

    HealthTextRender = CreateDefaultSubobject<UTextRenderComponent>("HealthTextRender");
    HealthTextRender->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
    Super::BeginPlay();
    check(HealthComponent);
    check(HealthTextRender);
    check(GetCharacterMovement());

    OnHealthChange(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &ABasePlayer::OnDeath);
    HealthComponent->OnHealthChange.AddUObject(this, &ABasePlayer::OnHealthChange);
}

// Called every frame
void ABasePlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ABasePlayer::MoveRight);
    PlayerInputComponent->BindAxis("TurnAround", this, &ABasePlayer::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &ABasePlayer::AddControllerPitchInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABasePlayer::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ABasePlayer::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ABasePlayer::OnStopRunning);

}

void ABasePlayer::MoveForward(float Amount)
{
    IsMovingForward = Amount > 0;
    if (Amount == 0) return;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ABasePlayer::MoveRight(float Amount)
{
    if (Amount == 0) return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void ABasePlayer::OnStartRunning()
{
    WentsToRun = true;
}

void ABasePlayer::OnStopRunning()
{
    WentsToRun = false;
}

bool ABasePlayer::IsRunning() const
{
    return WentsToRun && IsMovingForward && !GetVelocity().IsZero();
}

UHealthComponent* ABasePlayer::GetHealthComponent()
{
    return HealthComponent;
}

float ABasePlayer::GetMovementDirection()
{
    if (GetVelocity().IsZero())
        return 0.f;

    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ABasePlayer::OnDeath()
{
    UE_LOG(LogTemp, Warning, TEXT("Is Death %s "), *GetName())
        PlayAnimMontage(AnimDeath);
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(5.f);

    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}

void ABasePlayer::OnHealthChange(float Health)
{
    HealthTextRender->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}



