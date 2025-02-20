#include "TypeBase.h"
#include "BoolType.h"

namespace REFL
{ 
	const FBoolType* FTypeBase::AsBool()  const noexcept
	{
		return GetKind() == EValueKind::Boolean ? static_cast<const FBoolType*>(this) : nullptr;
	}
}