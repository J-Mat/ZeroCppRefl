#pragma once
#include "Core.h"
#include "Utils/EnumUtil.h"
#include "Any.h"

namespace REFL
{
	enum class EQualifier
	{
		None = 0x00,
		Const = 0x01,   // const vairble: const int, const int&, int* const
		Ref = 0x02,
	};
	DEFINE_ENUM_BIT_OPERATORS(EQualifier);


	namespace TypeModule
	{
		template <typename T>
		EQualifier GetQualifier()
		{
			EQualifier Qualifer = EQualifier::None;
			if constexpr (std::is_lvalue_reference_v<T>)
			{
				Qualifer |= EQualifier::Ref;
				if constexpr (std::is_const_v<std::remove_reference_t<T>>)
				{
					Qualifer |= EQualifier::Const;
				}
			}
			if constexpr (std::is_const_v<T>)
			{
				Qualifer |= EQualifier::Const;
			}
			return Qualifer;
		}
	}

	enum class EValueKind
	{
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
	EValueKind GetKindFromType()
	{
		if constexpr (Utils::bIsStdArray<T> || Utils::bIsVector<T> || std::is_array_v<T>)
		{
			return EValueKind::Array;
		}
		if constexpr (util::is_optional_v<T>)
		{
			return EValueKind::Optional;
		}
		if constexpr (std::is_pointer_v<T>)
		{
			return EValueKind::Pointer;
		}
		if constexpr (std::is_fundamental_v<T>)
		{
			return EValueKind::Numeric;
		}
		if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, std::string_view>)
		{
			return EValueKind::String;
		}
		if constexpr (std::is_enum_v<T>)
		{
			return EValueKind::Enum;
		}
		if constexpr (std::is_class_v<T>)
		{
			return EValueKind::Class;
		}
		return EValueKind::None;
	}

	class FBoolType;
	class FAny;
	class FTypeBase
	{
	public:
		using DefaultConstructFn = std::function<FAny(void)>;
		FTypeBase() = default;
		FTypeBase(const std::string& Name)
			: m_Name(Name) {}

		FTypeBase(const std::string& Name, DefaultConstructFn fn) : m_Name(Name), m_DefaultConstruct(fn) {}


		virtual EValueKind GetKind() const { return EValueKind::None; };
		std::string GetName() const noexcept { return m_Name; }

		const FBoolType* AsBool() const noexcept;

	protected:
		std::string m_Name;
		DefaultConstructFn m_DefaultConstruct;
	};

	namespace TypeModule
	{
		template <typename T>
		T* TryCast(FAny& Any)
		{
			if (TypeFactory::GetType<T>() == Any.GetType())
			{
				if (Any.GetAccessType() == FAny::EAccessType::Ref || Any.GetAccessType() == FAny::EAccessType::Copy)
				{
					return static_cast<T*>(Any.GetPayload());
				}
			}
			return nullptr;
		}

		template <typename T>
		const T* TryCastConst(const FAny& Any)
		{
			if (TypeFactory::GetType<T>() == Any.GetType())
			{
				return static_cast<T*>(Any.GetPayload());
			}
			return nullptr;
		}
	}

#define SET_VALUE_CHECK(Any, Type)                    \
    ((Any.GetAccessType() == FAny::EAccessType::Ref ||   \
      Any.GetAccessType() == FAny::EAccessType::Copy) && \
     Any.GetType()->GetKind() == Type)

#define COPY_VALUE_CHECK(Any, Type) \
    (Any.GetAccessType() != FAny::EAccessType::Null && Any.GetType()->GetKind() == Type)
}
