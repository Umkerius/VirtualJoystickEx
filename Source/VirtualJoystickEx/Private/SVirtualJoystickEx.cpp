#include "SVirtualJoystickEx.h"

void FZoneInfo::ResetTouchInside(bool NewTouchInside)
{
	if (TouchInside == NewTouchInside)
	{
		return;
	}

	TouchInside = NewTouchInside;
	if (NewTouchInside == Activated)
	{
		ElapsedTime = 0.0f;
	}
}

void SVirtualJoystickEx::AddZone(FName Name, float MinRadius, float MaxRadius, float StartAngle, float EndAngle, float ActivationTime)
{
	FZoneInfo& Zone = Zones.Add(Name);

	Zone.MinRadius = MinRadius;
	Zone.MaxRadius = MaxRadius;
	Zone.ActivationTime = ActivationTime;
	Zone.IsCircleZone = StartAngle == 0.0f && EndAngle == 360.0f;

	if (!Zone.IsCircleZone)
	{
		Zone.Cone = FCone(StartAngle, EndAngle);
	}
}

FZoneEnterEvent* SVirtualJoystickEx::GetZoneEnterEvent(FName Name)
{
	FZoneInfo* Zone = Zones.Find(Name);
	return Zone ? &Zone->EnterEvent : nullptr;
}

FZoneExitEvent* SVirtualJoystickEx::GetZoneExitEvent(FName Name)
{
	FZoneInfo* Zone = Zones.Find(Name);
	return Zone ? &Zone->ExitEvent : nullptr;
}

bool SVirtualJoystickEx::IsZoneActivated(FName Name) const
{
	const FZoneInfo* Zone = Zones.Find(Name);
	return Zone ? Zone->Activated : false;
}

bool SVirtualJoystickEx::HandleTouch(int32 ControlIndex, const FVector2D& LocalCoord, const FVector2D& ScreenSize)
{
	bool Result = SVirtualJoystick::HandleTouch(ControlIndex, LocalCoord, ScreenSize);

    const FControlData& ControlData = Controls[ControlIndex];
	FVector2D Offset = LocalCoord - ControlData.VisualCenter;

	if (Offset != FVector2D::ZeroVector)
	{
		float DistanceToTouchSqr;
		float DistanceToEdgeSqr;
		ComputeThumbPosition(ControlIndex, LocalCoord, &DistanceToTouchSqr, &DistanceToEdgeSqr);

		float Angle = FMath::Atan2(Offset.Y, Offset.X);
		HandleTouchInZones(DistanceToTouchSqr / DistanceToEdgeSqr, FMath::RadiansToDegrees(Angle));
	}
	else
	{
		HandleTouchInZones(0.0f, 0.0f);
	}

    return Result;
}

void SVirtualJoystickEx::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SVirtualJoystick::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	ProcessZones(InDeltaTime);
}

void SVirtualJoystickEx::HandleTouchInZones(float TouchRadiusPercent, float AngleDeg)
{
	float HeadingAngle = FCone::NormalizeAngle(AngleDeg + 90.0f);
	
	for (auto& KV : Zones)
	{
		FZoneInfo& Zone = KV.Value;
		Zone.ResetTouchInside(TouchRadiusPercent >= Zone.MinRadius && TouchRadiusPercent <= Zone.MaxRadius);

		if (!Zone.IsCircleZone)
		{
			Zone.ResetTouchInside(Zone.TouchInside && Zone.Cone.IsAngleInside(HeadingAngle));
		}
	}

	ProcessZones(0.0f);
}

void SVirtualJoystickEx::ProcessZones(float DeltaTime)
{
	for (auto& KV : Zones)
	{
		FZoneInfo& Zone = KV.Value;

		if (Zone.TouchInside != Zone.Activated)
		{
			Zone.ElapsedTime += DeltaTime;
			bool ShouldChangeState = Zone.ElapsedTime >= Zone.ActivationTime;

			if (ShouldChangeState)
			{
				Zone.Activated = Zone.TouchInside;
				Zone.ElapsedTime = 0.0f;
				
				if (Zone.Activated)
				{
					Zone.EnterEvent.Broadcast(KV.Key);
				}
				else
				{
					Zone.ExitEvent.Broadcast(KV.Key);
				}
			}
		}
	}
}

void SVirtualJoystickEx::ProcessZonesTouchEnd()
{
	for (auto& KV : Zones)
	{
		KV.Value.ResetTouchInside(false);
	}

	ProcessZones(0.0f);
}

FReply SVirtualJoystickEx::OnTouchStarted(const FGeometry& MyGeometry, const FPointerEvent& Event)
{
	FReply Reply = SVirtualJoystick::OnTouchStarted(MyGeometry, Event);
	if (Reply.IsEventHandled())
	{
		PressedEvent.Broadcast();
	}
	
	return Reply;
}

FReply SVirtualJoystickEx::OnTouchEnded(const FGeometry& MyGeometry, const FPointerEvent& Event)
{
	FReply Reply = SVirtualJoystick::OnTouchEnded(MyGeometry, Event);
	if (Reply.IsEventHandled())
	{
		ReleasedEvent.Broadcast();

		ProcessZonesTouchEnd();
	}
	
	return Reply;
}
