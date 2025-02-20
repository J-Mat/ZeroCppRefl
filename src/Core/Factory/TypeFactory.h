#pragma once
#include "Core.h"
#include "Type/TypeBase.h"
#include "Type/BoolType.h"
#include "Type/ClassType.h"
#include "PropertyFactory.h"
#include "Any.h"
#include "Utils/VariableTraits.hpp"

namespace REFL
{
	class FTypeDict final
	{
		public:
			static auto& Instance() 
			{
				static FTypeDict Inst;
				return Inst;
			}

			void Add(const FTypeBase* Type) 
			{
				if (Type && !Type->GetName().empty()) 
				{
					m_TypeMap.insert_or_assign(Type->GetName(), Type);
				}
			}

			const FTypeBase* Find(std::string_view Name) 
			{
				if (auto it = m_TypeMap.find(Name); it != m_TypeMap.end())  
				{
					return it->second;
				}
				return nullptr;
			}

			auto& GetTypeMap() const noexcept { return m_TypeMap; }

		private:
			std::unordered_map<std::string_view, const FTypeBase*> m_TypeMap;

			FTypeDict() = default;
	};

	class FBoolFactory final
	{
	public:
		static auto& Instance() noexcept
		{
			static FBoolFactory Inst;
			return Inst;
		}

		auto& GetType() const noexcept { return m_Type; }

	private:
			FBoolFactory() = default;
			FBoolType m_Type;
	};


	template <typename T>
	class FClassFactory final
	{
	private:
		static FAny DefaultConstruct()
		{
			if constexpr (std::is_default_constructible_v<T>)
			{
				return FAny{
						FAny::EAccessType::Copy, new T{},
						&TTypeOperationTraits<T>::GetOperations(),
						&FClassFactory<T>::Instance().GetType()
					};
			}
			else {
				return {};
			}
		}
	public:
		static auto& Instance() noexcept
		{
			static FClassFactory Inst;

			static bool bInited = false;
			if (!bInited)
			{
				bInited = true;
				if constexpr (std::is_default_constructible_v<T>)
				{
					Inst.m_ClassType.m_DefaultConstruct = DefaultConstruct;
				}
				FTypeDict::Instance().Add(&Inst.m_ClassType);
			}

			return Inst;
		}

		auto& Register(const std::string& Name) {
			m_ClassType.m_Name = Name;

			if (!FTypeDict::Instance().Find(Name)) 
			{
				FTypeDict::Instance().Add(&m_ClassType);
			} else
			{
			}

			return *this;
		}

		template <typename U>
		auto& Property(const std::string& Name, U Accessor) 
		{
			using Traits = Utils::TVariableTraits<U>;
			using Type = typename Traits::Type;

			Ref<FProperty> Prop = FPropertyFactory().Create(Name, Accessor);
			m_ClassType.m_Properties.emplace_back(
				Prop);

			return *this;
		}

		auto& GetType() const noexcept { return m_ClassType; }

	protected:
		FClassType m_ClassType;
		FClassFactory() = default;
	
	};


	template <typename T>
	class FTypeFactory final
	{
	public:
		static const FTypeBase* GetType() noexcept 
		{
			if constexpr (std::is_same_v<bool, T>) {
				return &FBoolFactory::Instance().GetType();
			}
			return nullptr;
		}
	};

	namespace FactoryModule
	{
		template <typename T>
		const FTypeBase* GetType() 
		{
			auto Type = FTypeFactory<T>::GetType();

			if (!Type) 
			{
				Type = &FClassFactory<T>::Instance().GetType();
			}

			return Type;
		}

		inline const FTypeBase* GetType(std::string_view Name) 
		{
			return FTypeDict::Instance().Find(Name);
		}

		template <typename T>
		FAny CallPropertyConst(const FAny& ClassAny, T Accessor, const FTypeBase* Owner)
		{
			if (Owner != ClassAny.GetType() || ClassAny.IsNull())
			{
				return {};
			}
			using Traits = Utils::TVariableTraits<T>;
			using Class = Traits::ClassType;
			using Type = Utils::TRemoveCVRef<typename Traits::Type>;

			auto& Value = ((Class*)ClassAny.GetPayload())->*Accessor;
			auto& Operations = TTypeOperationTraits<Type>::GetOperations();
			return {
				FAny::EAccessType::ConstRef,
				(void*)&Value,
				&Operations,
				GetType<Type>()
			};
		}

		template <typename T>
		FAny CallProperty(const FAny& ClassAny, T Accessor, const FTypeBase* Owner)
		{
			if (Owner != ClassAny.GetType() || ClassAny.IsNull())
			{
				return {};
			}
			using Traits = Utils::TVariableTraits<T>;
			using Class = Traits::ClassType;
			using Type = Utils::TRemoveCVRef<typename Traits::Type>;

			auto& Value = ((Class*)ClassAny.GetPayload())->*Accessor;
			auto& Operations = TTypeOperationTraits<Type>::GetOperations();
			return {
				ClassAny.IsConstRef() ? FAny::EAccessType::ConstRef : FAny::EAccessType::Ref,
				(void*)&Value,
				&Operations,
				GetType<Type>()
			};
		}
	}
}