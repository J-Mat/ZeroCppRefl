#pragma once
#include "Core.h"
#include "Property.h"
#include "../TypeBase.h"
#include "../ClassType.h"
/*

*/

namespace REFL
{
	class FProperty;
	class FBoolType;
	class FBoolProperty : public FProperty
	{
	public:
		FBoolProperty(const std::string& Name, const FClassType* Owner, EQualifier Qualifier);


		const struct FTypeBase* GetType() const noexcept override 
		{
			return (FTypeBase*)m_Type;
		}

	protected:
		const FBoolType* m_Type;
	};


	template <typename T>
	class FBoolPropertyImpl : public FBoolProperty {
	public:
		FBoolPropertyImpl(
			const std::string& Name, 
			const FClassType* Owner,
			EQualifier Q, 
			T Pointer
		):
			FBoolProperty(Name, Owner, Q), 
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