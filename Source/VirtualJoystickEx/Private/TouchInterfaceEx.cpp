#include "TouchInterfaceEx.h"
#include "SVirtualJoystickEx.h"

void UTouchInterfaceEx::Activate(TSharedPtr<SVirtualJoystick> VirtualJoystick)
{
    Super::Activate(VirtualJoystick);

	if (VirtualJoystick->GetType() == TEXT("SVirtualJoystickEx"))
	{
		auto VirtualJoystickEx = StaticCastSharedPtr<SVirtualJoystickEx>(VirtualJoystick);
		for (const FVirtualJoystickZone& Zone : VirtualJoystickZones)
		{
			VirtualJoystickEx->AddZone(Zone.Name, Zone.MinRadius, Zone.MaxRadius, Zone.StartAngle, Zone.EndAngle, Zone.ActivationTime);
		}
	}
}
