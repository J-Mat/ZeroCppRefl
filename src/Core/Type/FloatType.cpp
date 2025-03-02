#include "FloatType.h"

namespace REFL
{
	template <typename T>
	void DoSetValue(FAny& Any, T value) 
	{
		switch (Any.GetType()->AsFloat()->GetFloatKind()) 
		{
		case FFloatType::EFloatKind::Unknown:
			break;
		case FFloatType::EFloatKind::Float:
			*TryCast<float>(Any) = value;
			break;
		case FFloatType::EFloatKind::Double:
			*TryCast<double>(Any) = value;
			break;
		}
	}


	FFloatType::FFloatType(std::string Name, EFloatKind FloatKind):
		FTypeBase(Name, nullptr),
		m_Kind(FloatKind)
	{}

	void FFloatType::SetValue(FAny& Any, double Value) const
	{
		DoSetValue(Any, Value);
	}

	void FFloatType::SetValue(FAny& Any, float Value) const
	{
		DoSetValue(Any, Value);
	}

}