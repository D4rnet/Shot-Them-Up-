// Shoot Them Up Game, All Rights Reseved.

#include "Components/STUStaminaComponent.h"
#include "Player/STUBaseCharacter.h"
#include "Engine/World.h"
#include "TimerManager.h"

USTUStaminaComponent::USTUStaminaComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUStaminaComponent::BeginPlay()
{
    Super::BeginPlay();

    Stamina = MaxStamina;

    auto ComponentOwner = Cast<ASTUBaseCharacter>(GetOwner());

    if (ComponentOwner)
    {
        ComponentOwner->OnCharacterRun.AddUObject(this, &USTUStaminaComponent::RunningConsumption);
    }
}

void USTUStaminaComponent::RunningConsumption(float DeltaTime)
{
    SetStamina(Stamina - DeltaTime * StaminaConsumption);
}

void USTUStaminaComponent::SetStamina(float NewStamina)
{
    if (NewStamina < Stamina && StaminaRecovery && GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(StaminaRecoveryTimerHandle, this, &USTUStaminaComponent::OnStaminaRecovery,
            StaminaRecoveryUpdateTime, true, StaminaRecoveryDelay);
    }

    Stamina = FMath::Clamp(NewStamina, 0.0f, MaxStamina);
}

void USTUStaminaComponent::OnStaminaRecovery()
{
    SetStamina(Stamina + StaminaRecoveryModifier);

    if (FMath::IsNearlyEqual(MaxStamina, Stamina) && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(StaminaRecoveryTimerHandle);
    }
}
