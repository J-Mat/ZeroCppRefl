#include "BoolType.h"
#include "CastOp.hpp"

namespace REFL
{
	FBoolType::FBoolType() :
		FTypeBase("bool", nullptr) {}



	void FBoolType::SetValue(FAny& Dst, bool Value) const
	{
		//*CastModule::TryCast<bool>(Dst) = Value;
		*TryCast<bool>(Dst) = Value;
	}

	bool FBoolType::GetValue(const FAny& Any) const
	{
		//return *CastModule::TryCastConst<bool>(Any);
		return *TryCastConst<bool>(Any);
	}

}