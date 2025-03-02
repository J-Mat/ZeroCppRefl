#pragma once
#include "Core.h"
#include "Property.h"
#include "../TypeBase.h"
#include "../ClassType.h"

namespace REFL
{
	class FProperty;
	class FFloatType;
	class FFloatProperty : public FProperty
	{
	public:
		using FProperty::FProperty;
	};


	template <typename T>
	class FFloatPropertyImpl : public FFloatProperty {
	public:
		FFloatPropertyImpl(
			const std::string& Name, 
			const FClassType* Owner,
			EQualifier Q, 
			T Pointer
		):
			FFloatProperty(Name, Owner, Q),
			m_Pointer(Pointer),
			m_Type(&FFloatFactory<Utils::TRemoveCVRef <Utils::TVariableTraits<T>>::Type>::Instance().GetType())
		{
		}

		FAny CallConst(const FAny& Any) const override {
			return FactoryModule::CallPropertyConst(Any, m_Pointer, m_Owner);
		}

		FAny Call(FAny& ClassAny) const override 
		{
			return FactoryModule::CallProperty(ClassAny, m_Pointer, m_Owner);
		}

		const struct FTypeBase* GetType() const noexcept override 
		{
			return (FTypeBase*)m_Type;
		}

	private:
		T m_Pointer;
		const class FFloatType* m_Type;
	};
}