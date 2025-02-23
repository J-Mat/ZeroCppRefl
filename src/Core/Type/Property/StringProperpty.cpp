#include "StringProperpty.h"	
#include "Factory/TypeFactory.h"


namespace REFL
{
	FStringProperty::FStringProperty(const std::string& Name, const FClassType* Owner, EQualifier Qualifier)
		: FProperty(Name, Owner, Qualifier),
		m_Type(&FStringFactory::Instance().GetType())
	{
	}
}