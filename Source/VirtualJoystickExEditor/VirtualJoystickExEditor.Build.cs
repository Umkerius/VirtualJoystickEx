using UnrealBuildTool;

public class VirtualJoystickExEditor : ModuleRules
{
	public VirtualJoystickExEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PrivateDependencyModuleNames.AddRange(new[]
		{
			"Core",
			"InputCore",
			"UnrealEd",
			"LevelEditor",
			"CoreUObject",
			"Engine",
			"VirtualJoystickEx"
		});
	}
}
