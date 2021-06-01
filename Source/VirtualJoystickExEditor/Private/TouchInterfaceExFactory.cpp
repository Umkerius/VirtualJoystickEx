#include "TouchInterfaceExFactory.h"
#include "TouchInterfaceEx.h"

UTouchInterfaceExFactory::UTouchInterfaceExFactory()
{
    SupportedClass = UTouchInterfaceEx::StaticClass();

    bCreateNew = true;
    bEditorImport = false;
    bEditAfterNew = true;
}

UObject* UTouchInterfaceExFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
    return NewObject<UTouchInterfaceEx>(InParent, Name, Flags);
}
