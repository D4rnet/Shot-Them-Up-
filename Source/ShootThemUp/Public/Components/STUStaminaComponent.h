// Shoot Them Up Game, All Rights Reseved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUStaminaComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUStaminaComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTUStaminaComponent();

    UFUNCTION(BlueprintCallable, Category = "Stamina")
    float GetStaminaPercent() const { return Stamina / MaxStamina; }

    float GetStamina() const { return Stamina; }

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina", meta = (ClampMin = "0", ClampMax = "1000"))
    float MaxStamina = 50.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina", meta = (ClampMin = "0", ClampMax = "1000"))
    float StaminaConsumption = 5.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "StaminaRecovery")
    bool StaminaRecovery = true;

    UPROPERTY(
        EditDefaultsOnly, BlueprintReadWrite, Category = "StaminaRecovery", meta = (ClampMin = "0.0", ClampMax = "10.0", EditCondition = "StaminaRecovery"))
    float StaminaRecoveryUpdateTime = 0.1f;

    UPROPERTY(
        EditDefaultsOnly, BlueprintReadWrite, Category = "StaminaRecovery", meta = (ClampMin = "0.0", ClampMax = "10.0", EditCondition = "StaminaRecovery"))
    float StaminaRecoveryDelay = 2.0f;

    UPROPERTY(
        EditDefaultsOnly, BlueprintReadWrite, Category = "StaminaRecovery", meta = (ClampMin = "0.0", ClampMax = "10.0", EditCondition = "StaminaRecovery"))
    float StaminaRecoveryModifier = 1.0f;

private:
    float Stamina = 0.0f;

    FTimerHandle StaminaRecoveryTimerHandle;

    void SetStamina(float NewStamina);
    void OnStaminaRecovery();

    void RunningConsumption(float DeltaTime);
};
