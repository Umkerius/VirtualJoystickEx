#pragma once
#include "Factories/Factory.h"
#include "TouchInterfaceExFactory.generated.h"

UCLASS(hidecategories=Object)
class UTouchInterfaceExFactory : public UFactory
{
    GENERATED_BODY()
public:
    UTouchInterfaceExFactory();
    virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
