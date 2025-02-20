#include "BoolType.h"

namespace REFL
{
	FBoolType::FBoolType() :
		FTypeBase("bool", nullptr) {}



	void FBoolType::SetValue(FAny& Dst, bool Value) const
	{
		//*TypeModule::TryCast<bool>(Dst) = Value;
	}

	bool FBoolType::GetValue(const FAny& Any) const
	{
		//return *TypeModule::TryCastConst<bool>(Any);
		return true;
	}

}