#pragma once
#include "AssetTypeActions_Base.h"

class FAssetTypeActions_TouchInterfaceEx : public FAssetTypeActions_Base
{
public:
    FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_TouchInterfaceEx", "Touch Interface Ex Setup"); }
    FColor GetTypeColor() const override { return FColor(175, 0, 128); }
    UClass* GetSupportedClass() const override;
    uint32 GetCategories() override { return EAssetTypeCategories::Misc; }
};
