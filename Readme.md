# Unreal Engine Virtual Joystick Extension
VirtualJoystickEx is a plugin whose main purpose is to show how to extend Unreal Engine virtual joystick functionality\
This plugin requires UE version > 4.26 (was tested in UE5.0EA). To compile it with your project SlateCore and Slate dependencies must be added in game module.

To use VirtualJoystickEx, APlayerController::CreateVirtualJoystick method must be overriden:
```c++
virtual TSharedPtr<SVirtualJoystick> CreateVirtualJoystick() override
{
    return SNew(SVirtualJoystickEx);
}
```
The next step is creating TouchInterfaceEx asset in Content Browser (Micsellaneous/Touch Interface Ex Setup), setting it up and set the asset as default touch interface in Project Settings/Input
## Features
* Joystick Pressed/Released events
* Zones: circular and conical with ability of getting enter/exit events
## Usage in code
Get VirtualJoystickEx from player controller, add new zone (or setup in TouchInterfaceEx asset) and subscribe on zone events:
```c++
auto PlayerController = GetController<AMyPlayerController>();
TSharedPtr<SVirtualJoystickEx> JoyStick = PlayerController ? PlayerController->GetVirtualJoystick() : nullptr;
	
if (JoyStick.IsValid())
{
  JoyStick->AddZone("Sprint", 1.0f, 10.0f, 330.0f, 30.0f, 0.3f);
  JoyStick->GetZoneEnterEvent("Sprint")->AddWeakLambda(this, [this](FName)
  {
    bSprintHeld = true;
  });

  JoyStick->GetZoneExitEvent("Sprint")->AddWeakLambda(this, [this](FName)
  {
    bSprintHeld = false;
  });
}
```
## Extending
Inherit from VirtualJoystickEx, make what you want.\
To able making of specified touch interface assets, asset factory and asset type actions classes must be implemented. Also asset type actions class must be registered in Asset Tools module. For more information see [VirtualJoystickExEditor](https://github.com/Umkerius/VirtualJoystickEx/tree/master/Source/VirtualJoystickExEditor) module.
