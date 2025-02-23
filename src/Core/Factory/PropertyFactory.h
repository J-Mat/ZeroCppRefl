#pragma once
#include "Core.h"
#include "Type/TypeBase.h"
#include "TypeFactory.h"
#include "./Utils/VariableTraits.hpp"
#include "./Utils/Misc.hpp"
#include "Type/Property/BoolProperpty.h"
#include "Type/Property/StringProperpty.h"

namespace REFL
{
	class FBoolProperty;
	class FBoolPropertyFactory final
	{
	public:
		template <typename T>
		FBoolPropertyFactory(const std::string& Name, T Accessor) 
		{
			using Traits = Utils::TVariableTraits<T>;
			using Type = Traits::Type;
			using Class = Traits::ClassType;
			m_Property = CreateRef<FBoolPropertyImpl<T>>(
				Name,
				&FClassFactory<Class>::Instance().GetType(),
				TypeModule::GetQualifier<Type>(),
				Accessor
			);
		}
		auto& GetProperty() noexcept { return m_Property; }
	private:
		Ref<FBoolProperty> m_Property;
	};

	class FStringProperty;
	class FStringPropertyFactory final
	{
	public:
		template <typename T>
		FStringPropertyFactory(const std::string& Name, T Accessor)
		{
			using Traits = Utils::TVariableTraits<T>;
			using Type = Traits::Type;
			using Class = Traits::ClassType;
			m_Property = CreateRef<FStringPropertyImpl<T>>(
				Name,
				&FClassFactory<Class>::Instance().GetType(),
				TypeModule::GetQualifier<Type>(),
				Accessor
			);
		}
		auto& GetProperty() noexcept { return m_Property; }
	private:
		Ref<FStringProperty> m_Property;
	};

	class FPropertyFactory final
	{
	public:
		template <typename T>
		Ref<FProperty> Create(const std::string& Name, T Accessor) 
		{
			using Traits = Utils::TVariableTraits<T>;
			using Type = Utils::TRemoveCVRef<typename Traits::Type>;
			if constexpr (std::is_same_v<bool, Type>) 
			{
				return FBoolPropertyFactory(Name, Accessor).GetProperty();
			}
			else if constexpr (std::is_same_v<std::string, Type>) 
			{
				return FStringPropertyFactory(Name, Accessor).GetProperty();
			}
			return nullptr;
		}
	};
}