#pragma once
#include <CoreMinimal.h>

class VIRTUALJOYSTICKEX_API FCone
{
public:
	FCone() = default;
	FCone(const FCone&) = default;
	FCone(float StartAngle, float EndAngle);

	bool IsAngleInside(float AngleDeg) const;
	static float NormalizeAngle(float Angle);

private:
	static float CalculateConeHalfAngleDot(float StartAngle, float EndAngle, float& HalfAngle);
	static FVector2D AngleToDirection(float Angle);

	FVector2D ConeDir;
	float HalfAngleDot;
};
