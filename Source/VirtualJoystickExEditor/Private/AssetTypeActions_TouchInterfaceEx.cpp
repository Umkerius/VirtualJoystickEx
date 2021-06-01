#include "AssetTypeActions_TouchInterfaceEx.h"
#include "TouchInterfaceEx.h"

UClass* FAssetTypeActions_TouchInterfaceEx::GetSupportedClass() const
{
    return UTouchInterfaceEx::StaticClass();
}
