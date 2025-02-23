#pragma once
#include "Type/TypeBase.h"
#include "OperationTrait.hpp"

namespace REFL
{
	class FTypeBase;
	struct FTypeOperations;
	class FAny;

	template <typename T>
	T* TryCast(FAny&);

	template <typename T>
	const T* TryCastConst(const FAny&);

	class FAny
	{
	public:
		template <typename T>
		friend T* TryCast(FAny&);

		template <typename T>
		friend const T* TryCastConst(const FAny&);


		enum class EAccessType {
			Null,
			ConstRef,
			Ref,
			Copy,
		};
		FAny() = default;
		FAny(EAccessType AccessType, void* Payload, const FTypeOperations* TypeOperations, const FTypeBase* Type):
			m_AccessType(AccessType),
			m_Payload(Payload),
			m_Operations(TypeOperations),
			m_Type(Type) {}
		const FTypeBase* GetType() const {return m_Type;}
		EAccessType GetAccessType() const {return m_AccessType;}
		const void* GetPayload() const {return m_Payload;}
		void* GetPayload() {return m_Payload;}

		bool IsConstRef() const noexcept {return m_AccessType == EAccessType::ConstRef;}
		bool IsNull() const noexcept {return m_AccessType == EAccessType::Null;}
		bool IsCopy() const noexcept {return m_AccessType == EAccessType::Copy;}
		const  FTypeOperations* GetOperations() { return m_Operations; }

	private:
		int* p = nullptr;
		const FTypeBase* m_Type = nullptr;
		enum EAccessType m_AccessType = EAccessType::Null;
		const FTypeOperations* m_Operations = FTypeOperations::NullPtr();
		void* m_Payload = nullptr;
	};
	
	namespace AnyModule
	{
		template <typename T>
		FAny MakeCopyAny(T&& Value) 
		{
			using Type = Utils::TRemoveCVRef<T>;
			void* Elem = nullptr;
			try {
				if constexpr (std::is_enum_v<T>)
				{
					Elem = new long{static_cast<long>(Value)}
				}
				else
				{
					Elem = new Type{std::forward<T>(Value)}
				}
			}
			catch (const std::bad_alloc&)
			{
				Elem = nullptr;
			}
			return {
				FAny::EAccessType::Copy,
				Elem,
				&TTypeOperationTraits<Type>::GetOperations(),
				FactoryModule::GetType<Utils::TRemoveCVRef<T>>()
			};
		}


		template <typename T>
		FAny MakeRefAny(T& Value) noexcept 
		{
			using Type = Utils::TRemoveCVRef<T>;
			return { 
				FAny::EAccessType::Ref, 
				(void*)&Value,
				&TTypeOperationTraits<Type>::GetOperations(),
				FactoryModule::GetType<Utils::TRemoveCVRef<T>>()
			};
		}
	}
}