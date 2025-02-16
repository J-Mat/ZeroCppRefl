#pragma once
#include "Core.h"
#include "../Utils/Misc.hpp"
#include "../Any.hpp"
#include "../Factory.hpp"

namespace REFL
{
	enum class EQualifier
	 {
		None = 0x00,
		Const = 0x01,   // const vairble: const int, const int&, int* const
		Ref = 0x02,
	};

	enum class EValueKind {
		None,
		Boolean,
		Numeric,
		String,
		Enum,
		Class,
		Property,
		Pointer,
		Array,
		Optional,
	};

	template <typename T>
	EValueKind GetKindFromType() {
		if constexpr (Utils::bIsStdArray<T> || Utils::bIsVector<T> ||
				std::is_array_v<T>) {
			return EValueKind::Array;
		}
		if constexpr (util::is_optional_v<T>) {
			return EValueKind::Optional;
		}
		if constexpr (std::is_pointer_v<T>) {
			return EValueKind::Pointer;
		}
		if constexpr (std::is_fundamental_v<T>) {
			return EValueKind::Numeric;
		}
		if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, std::string_view>) {
			return EValueKind::String;
		}
		if constexpr (std::is_enum_v<T>) {
			return EValueKind::Enum;
		}
		if constexpr (std::is_class_v<T>) {
			return EValueKind::Class;
		}

		return EValueKind::None;
	}


	class FAny;
	class FType
	{
		using DefaultConstructFn = std::function<FAny(void)>;
	public:
		FType(const std::string& Name)
        : m_Name(Name) {}

		FType(std::string Name, DefaultConstructFn fn): m_Name(Name),  m_DefaultConstruct(fn) {}


		virtual EValueKind GetKind() const = 0;
		std::string GetName() const noexcept {return m_Name;}

	private:
		std::string m_Name;
		DefaultConstructFn m_DefaultConstruct;
	};


	template <typename T>
	T* TryCast(FAny& Any) {
    if (GetType<T>() == Any.GetType()) 
	{
        if (Any.GetAccessType() == FAny::EAccessType::Ref || Any.GetAccessType() == FAny::EAccessType::Copy) 
		{
            return static_cast<T*>(Any.GetPayload());
        }
    }
		throw bad_any_access{"can't cast mutable type from const reference"};
		return nullptr;
	}

	template <typename T>
	const T* TryCastConst(const FAny& Any) 
	{
		if (typeinfo<T>() == Any.GeteType()) 
		{
			return static_cast<T*>(Any.GetPayload());
		}
		return nullptr;
	}

} // namespace DREF
