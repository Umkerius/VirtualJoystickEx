#include "Cone.h"

FCone::FCone(float StartAngle, float EndAngle)
{
	float HalfAngle;
	HalfAngleDot = CalculateConeHalfAngleDot(StartAngle, EndAngle, HalfAngle);
	ConeDir = AngleToDirection(StartAngle + HalfAngle);
}

bool FCone::IsAngleInside(float AngleDeg) const
{
	FVector ConeDirection(ConeDir, 0.0f);
	FVector ObservedDirection = FVector(AngleToDirection(AngleDeg), 0.0f);
	
	return ConeDirection.CosineAngle2D(ObservedDirection) >= HalfAngleDot;
}

float FCone::NormalizeAngle(float Angle)
{
	if (Angle >= 360.0f)
	{
		Angle -= 360.0f;
	}
	else if (Angle < 0)
	{
		Angle += 360.0f;
	}

	return Angle;
}

float FCone::CalculateConeHalfAngleDot(float StartAngle, float EndAngle, float& HalfAngle)
{
	float AngleDiff = NormalizeAngle(EndAngle - StartAngle);
	HalfAngle = AngleDiff / 2.0f;
	
	return FMath::Cos(FMath::DegreesToRadians(HalfAngle));
}

FVector2D FCone::AngleToDirection(float Angle)
{
	Angle = NormalizeAngle(Angle);
	return FVector2D(1.0f, 0.0f).GetRotated(Angle);
}
