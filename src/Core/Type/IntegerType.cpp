#include "IntegerType.h"

namespace REFL
{
	template <typename T>
	void DoSetValue(FAny& Any, T value) 
	{
		switch (Any.GetType()->AsInteger()->GetIntegerKind()) 
		{
		case FIntegerType::EIntergerKind::Unknown:
			break;
		case FIntegerType::EIntergerKind::Char:
			*TryCast<char>(Any) = value;
			break;
		case FIntegerType::EIntergerKind::Int:
			*TryCast<int>(Any) = value;
			break;
		case FIntegerType::EIntergerKind::Short:
			*TryCast<short>(Any) = value;
			break;
		case FIntegerType::EIntergerKind::LongLong:
			*TryCast<long long>(Any) = value;
			break;
		case FIntegerType::EIntergerKind::Uint8:
			*TryCast<uint8_t>(Any) = value;
			break;
		case FIntegerType::EIntergerKind::Uint16:
			*TryCast<uint16_t>(Any) = value;
			break;
		case FIntegerType::EIntergerKind::Uint32:
			*TryCast<uint32_t>(Any) = value;
			break;
		case FIntegerType::EIntergerKind::Uint64:
			*TryCast<uint64_t>(Any) = value;
			break;
		}
	}


	FIntegerType::FIntegerType(std::string Name, EIntergerKind IntergerKind):
		FTypeBase(Name, nullptr),
		m_Kind(IntergerKind)
	{}

	void FIntegerType::SetValue(FAny& Any, long Value) const
	{
		DoSetValue(Any, Value);
	}

	void FIntegerType::SetValue(FAny& Any, uint64_t Value) const
	{
		DoSetValue(Any, Value);
	}

}