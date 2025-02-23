#pragma once
#include "Factory/TypeFactory.h"

namespace REFL
{
	template <typename T>
	T* TryCast(FAny& Any)
	{
		if (FactoryModule::GetType<T>() == Any.GetType())
		{
			if (Any.GetAccessType() == FAny::EAccessType::Ref || Any.GetAccessType() == FAny::EAccessType::Copy)
			{
				return static_cast<T*>(Any.GetPayload());
			}
		}
		return nullptr;
	}

	template <typename T>
	const T* TryCastConst(const FAny& Any)
	{
		if (FactoryModule::GetType<T>() == Any.GetType())
		{
			return static_cast<T*>(Any.m_Payload);
		}
		return nullptr;
	}
}