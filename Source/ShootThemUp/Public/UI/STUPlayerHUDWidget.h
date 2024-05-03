// Shoot Them Up Game, All Rights Reseved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUPlayerHUDWidget.generated.h"

UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, category = "UI")
    float GetHelthPercent() const;

    UFUNCTION(BlueprintCallable, category = "UI")
    float GetStaminaPercent() const;

    UFUNCTION(BlueprintCallable, category = "UI")
    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

    UFUNCTION(BlueprintCallable, category = "UI")
    bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

    UFUNCTION(BlueprintCallable, category = "UI")
    bool IsPlayerAlive() const;

    UFUNCTION(BlueprintCallable, category = "UI")
    bool IsPlayerSpectating() const;

    UFUNCTION(BlueprintImplementableEvent, category = "UI")
    void OnTakeDamage();

    virtual bool Initialize() override;

private:
    void OnHealthChanged(float Health, float HealthDelta);
};
