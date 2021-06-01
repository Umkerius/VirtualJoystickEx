#pragma once
#include <Widgets/Input/SVirtualJoystick.h>
#include "Cone.h"

DECLARE_EVENT(SVirtualJoystickEx, FJoystickActivationEvent)

DECLARE_EVENT_OneParam(SVirtualJoystickEx, FZoneEnterEvent, FName);
DECLARE_EVENT_OneParam(SVirtualJoystickEx, FZoneExitEvent, FName);

struct VIRTUALJOYSTICKEX_API FZoneInfo
{
    float MinRadius;
    float MaxRadius;
    FCone Cone;
    float ActivationTime;

    FZoneEnterEvent EnterEvent;
    FZoneExitEvent ExitEvent;

    float ElapsedTime = 0.0f;
    bool TouchInside = false;
    bool IsCircleZone;
    bool Activated = false;

    void ResetTouchInside(bool NewTouchInside);
};

class VIRTUALJOYSTICKEX_API SVirtualJoystickEx : public SVirtualJoystick
{
public:
    FJoystickActivationEvent& OnPressed() { return PressedEvent; }
    FJoystickActivationEvent& OnReleased() { return ReleasedEvent; }

    void AddZone(FName Name, float MinRadius, float MaxRadius, float StartAngle = 0.0f, float EndAngle = 360.0f, float ActivationTime = 0.0f);
    FZoneEnterEvent* GetZoneEnterEvent(FName Name);
    FZoneExitEvent* GetZoneExitEvent(FName Name);
    
    bool IsZoneActivated(FName Name) const;
    
protected:
    virtual bool HandleTouch(int32 ControlIndex, const FVector2D& LocalCoord, const FVector2D& ScreenSize) override;
    virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

    void HandleTouchInZones(float TouchRadiusPercent, float AngleDeg);
    void ProcessZones(float DeltaTime);
    void ProcessZonesTouchEnd();

    virtual FReply OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& Event) override;
    virtual FReply OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& Event) override;

    FJoystickActivationEvent PressedEvent;
    FJoystickActivationEvent ReleasedEvent;
    TMap<FName, FZoneInfo> Zones;
};
