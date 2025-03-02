#include "TypeBase.h"
#include "BoolType.h"
#include "StringType.h"
#include "FloatType.h"
#include "IntegerType.h"

namespace REFL
{ 
	const FBoolType* FTypeBase::AsBool()  const noexcept
	{
		return GetTypeKind() == EValueKind::Boolean ? static_cast<const FBoolType*>(this) : nullptr;
	}

	const FStringType* FTypeBase::AsString() const noexcept
	{
		return GetTypeKind() == EValueKind::String ? static_cast<const FStringType*>(this) : nullptr;
	}

	const FIntegerType* FTypeBase::AsInteger() const noexcept
	{
		return GetTypeKind() == EValueKind::Integer ? static_cast<const FIntegerType*>(this) : nullptr;
	}
	const FFloatType* FTypeBase::AsFloat() const noexcept
	{
		return GetTypeKind() == EValueKind::Float ? static_cast<const FFloatType*>(this) : nullptr;
	}

}