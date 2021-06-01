#include <Modules/ModuleManager.h>
#include <IAssetTools.h>
#include "AssetTypeActions_TouchInterfaceEx.h"

class FVirtualJoystickExEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override 
	{
		IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
		AssetTools.RegisterAssetTypeActions(MakeShared<FAssetTypeActions_TouchInterfaceEx>());
	}
};

IMPLEMENT_MODULE(FVirtualJoystickExEditorModule, VirtualJoystickExEditor)
