#pragma once
#include "Core.h"
#include "Property.h"
#include "../TypeBase.h"
#include "../ClassType.h"
#include "../BoolType.h"
#include "Factory/TypeFactory.h"


namespace REFL
{
	class FProperty;
	class FBoolProperty : public FProperty
	{
	public:
		FBoolProperty(const std::string& Name, const FClassType* Owner, EQualifier q)
			: FProperty(Name, Owner, q),
			m_Type(&FBoolFactory::Instance().GetType()) {}


		const struct FTypeBase* GetType() const noexcept override {
			return m_Type;
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
			std::cout << ClassAny.GetType() << std::endl;
			std::cout << m_Owner << std::endl;
			std::cout << REFL::FactoryModule::GetType<Person>() << std::endl;
			return FactoryModule::CallProperty(ClassAny, m_Pointer, m_Owner);
		}

	private:
		T m_Pointer;
	};
}