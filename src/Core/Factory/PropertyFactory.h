#pragma once
#include "Core.h"
#include "Type/TypeBase.h"
#include "TypeFactory.h"
#include "./Utils/VariableTraits.hpp"
#include "./Utils/Misc.hpp"
#include "Type/Property/BoolProperpty.h"
#include "Type/Property/StringProperty.h"
#include "Type/Property/IntegerProperpty.h"
#include "Type/Property/FloatProperpty.h"

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


	class FIntegerProperty;
	class FIntegerPropertyFactory final
	{
	public:
		template <typename T>
		FIntegerPropertyFactory(const std::string& Name, T Accessor)
		{
			using Traits = Utils::TVariableTraits<T>;
			using Type = Traits::Type;
			using Class = Traits::ClassType;
			m_Property = CreateRef<FIntegerPropertyImpl<T>>(
				Name,
				&FClassFactory<Class>::Instance().GetType(),
				TypeModule::GetQualifier<Type>(),
				Accessor
			);
		}
		auto& GetProperty() noexcept { return m_Property; }
	private:
		Ref<FIntegerProperty> m_Property;
	};

	class FFloatProperty;
	class FFloatPropertyFactory final
	{
	public:
		template <typename T>
		FFloatPropertyFactory(const std::string& Name, T Accessor)
		{
			using Traits = Utils::TVariableTraits<T>;
			using Type = Traits::Type;
			using Class = Traits::ClassType;
			m_Property = CreateRef<FFloatPropertyImpl<T>>(
				Name,
				&FClassFactory<Class>::Instance().GetType(),
				TypeModule::GetQualifier<Type>(),
				Accessor
			);
		}
		auto& GetProperty() noexcept { return m_Property; }
	private:
		Ref<FFloatProperty> m_Property;
	};

	class FEnumProperty;
	class FEnumPropertyFactory final
	{
	public:
		template <typename T>
		FEnumPropertyFactory(const std::string& Name, T Accessor)
		{
			using Traits = Utils::TVariableTraits<T>;
			using Type = Traits::Type;
			using Class = Traits::ClassType;
			m_Property = CreateRef<FEnumPropertyImpl<T>>(
				Name,
				&FClassFactory<Class>::Instance().GetType(),
				TypeModule::GetQualifier<Type>(),
				Accessor
			);
		}
		auto& GetProperty() noexcept { return m_Property; }
	private:
		Ref<FEnumProperty> m_Property;
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
			else if constexpr (std::is_integral_v<Type>) 
			{
				return FIntegerPropertyFactory(Name, Accessor).GetProperty();
			}
			else if constexpr (std::is_floating_point_v<Type>) 
			{
				return FFloatPropertyFactory(Name, Accessor).GetProperty();
			}
			else if constexpr (std::is_enum_v<Type>)
			{
				return FEnumPropertyFactory(Name, Accessor).GetProperty();
			}
			return nullptr;
		}
	};
}