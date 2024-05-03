// Shoot Them Up Game, All Rights Reseved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUHealthComponent.generated.h"

class UCameraShakeBase;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTUHealthComponent();

    FOnDeathSignature OnDeath;
    FOnHealthChangedSignature OnHealthChanged;

    UFUNCTION(BlueprintCallable, category = "Health")
    bool IsDead() const { return FMath::IsNearlyZero(Health); }

    UFUNCTION(BlueprintCallable, category = "Health")
    float GetHelthPercent() const { return Health / MaxHealth; }

    float GetHealth() const { return Health; }

    bool TryToAddHealth(float HealthAmount);
    bool IsHealthFull() const;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
    float MaxHealth = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    bool AutoHeal = true;

    UPROPERTY(
        EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (ClampMin = "0.0", ClampMax = "10.0", EditCondition = "AutoHeal"))
    float HealUpdateTime = 1.0f;

    UPROPERTY(
        EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (ClampMin = "0.0", ClampMax = "10.0", EditCondition = "AutoHeal"))
    float HealDelay = 3.0f;

    UPROPERTY(
        EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (ClampMin = "0.0", ClampMax = "10.0", EditCondition = "AutoHeal"))
    float HealModifier = 5.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TSubclassOf<UCameraShakeBase> CameraShake;

    virtual void BeginPlay() override;

private:
    float Health = 0.0f;

    FTimerHandle HealTimerHandle;

    UFUNCTION()
    void OnTakeAnyDamage(
        AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

    void OnAutoHeal();
    void SetHealth(float NewHealth);

    void PlayCameraShake();
};
