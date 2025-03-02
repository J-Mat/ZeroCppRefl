#include "EnumProperty.h"

namespace REFL
{ 
	FEnumProperty::FEnumProperty(const std::string& Name, const FClassType* Owner, EQualifier Qualifier):
		FProperty(Name, Owner, Qualifier)
	{
	}
}

