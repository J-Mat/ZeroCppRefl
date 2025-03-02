#pragma once
#include "Core.h"
#include "Property.h"
#include "../TypeBase.h"
#include "../ClassType.h"

namespace REFL
{
	class FProperty;
	class FEnumType;
	class FEnumProperty : public FProperty
	{
	public:
		FEnumProperty(const std::string& Name, const FClassType* Owner, EQualifier Qualifier);
	};
	
	template <typename T>
	class FEnumPropertyImpl : public FEnumProperty 
	{
	public:
		FEnumPropertyImpl(
			const std::string& Name, 
			const FClassType* Owner, 
			EQualifier Q,
			T Pointer
		): FEnumProperty(Name, Owner, Q),
			m_Pointer(Pointer),
			m_Type(&FEnumFactory<Utils::TRemoveCVRef <Utils::TVariableTraits<T>>::Type>::Instance().GetType()) 
		{
		}

		const struct FTypeBase* GetType() const noexcept override 
		{
			return (FTypeBase*)m_Type;
		}

		FAny CallConst(const FAny& Any) const override 
		{
			return FactoryModule::CallPropertyConst(Any, m_Pointer, m_Owner);
		}

		FAny Call(FAny& Any) const override 
		{
			return FactoryModule::CallProperty(Any, m_Pointer, m_Owner);
		}

	private:
		T m_Pointer = nullptr;
		const class FEnumType* m_Type = nullptr;
	};
	
}