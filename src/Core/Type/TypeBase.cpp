#include "TypeBase.h"
#include "BoolType.h"
#include "StringType.h"

namespace REFL
{ 
	const FBoolType* FTypeBase::AsBool()  const noexcept
	{
		return GetKind() == EValueKind::Boolean ? static_cast<const FBoolType*>(this) : nullptr;
	}

	const FStringType* FTypeBase::AsString() const noexcept
	{
		return GetKind() == EValueKind::String ? static_cast<const FStringType*>(this) : nullptr;
	}

}