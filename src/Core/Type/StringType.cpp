#include "StringType.h"
#include "CastOp.hpp"

namespace REFL
{
	FStringType::FStringType() :
		FTypeBase("string", nullptr) {}

	void FStringType::SetValue(FAny& Dst, std::string Str) const
	{
		*TryCast<std::string>(Dst) = Str;
	}

	std::string FStringType::GetValue(const FAny& Any) const
	{
		return *TryCastConst<std::string>(Any);
	}

}