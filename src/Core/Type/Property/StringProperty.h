#pragma once
#include "Core.h"
#include "Property.h"
#include "../TypeBase.h"
#include "../ClassType.h"

namespace REFL
{
	class FProperty;
	class FStringType;
	class FStringProperty : public FProperty
	{
	public:
		FStringProperty(const std::string& Name, const FClassType* Owner, EQualifier Qualifier);


		const struct FTypeBase* GetType() const noexcept override 
		{
			return (FTypeBase*)m_Type;
		}

	protected:
		const FStringType* m_Type;
	};


	template <typename T>
	class FStringPropertyImpl : public FStringProperty {
	public:
		FStringPropertyImpl(
			const std::string& Name, 
			const FClassType* Owner,
			EQualifier Q, 
			T Pointer
		):
			FStringProperty(Name, Owner, Q), 
			m_Pointer(Pointer) 
		{}

		FAny CallConst(const FAny& Any) const override {
			return FactoryModule::CallPropertyConst(Any, m_Pointer, m_Owner);
		}

		FAny Call(FAny& ClassAny) const override 
		{
			return FactoryModule::CallProperty(ClassAny, m_Pointer, m_Owner);
		}

	private:
		T m_Pointer;
	};
}