#include "BoolProperpty.h"	
#include "Factory/TypeFactory.h"


namespace REFL
{
	FBoolProperty::FBoolProperty(const std::string& Name, const FClassType* Owner, EQualifier Qualifier)
		: FProperty(Name, Owner, Qualifier),
		m_Type(&FBoolFactory::Instance().GetType())
	{
	}
}