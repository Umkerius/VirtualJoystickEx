#pragma once
#include <GameFramework/TouchInterface.h>
#include "TouchInterfaceEx.generated.h"

USTRUCT(BlueprintType)
struct FVirtualJoystickZone
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    FName Name;

    UPROPERTY(EditAnywhere)
    float MinRadius = 0.0f;

    UPROPERTY(EditAnywhere)
    float MaxRadius = 0.0f;

    UPROPERTY(EditAnywhere)
    float StartAngle = 0.0f;

    UPROPERTY(EditAnywhere)
    float EndAngle = 360.0f;

    UPROPERTY(EditAnywhere)
    float ActivationTime = 0.0f;
};

UCLASS(Blueprintable, BlueprintType)
class VIRTUALJOYSTICKEX_API UTouchInterfaceEx : public UTouchInterface
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, Category = "TouchInterface", meta = (ToolTip = "Virtual joystick zones"))
    TArray<FVirtualJoystickZone> VirtualJoystickZones;

    virtual void Activate(TSharedPtr<SVirtualJoystick> VirtualJoystick) override;
};