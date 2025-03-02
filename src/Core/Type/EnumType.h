#pragma once
#include "Core.h"
#include "TypeBase.h"
#include "Any.h"
#include "CastOp.hpp"

namespace REFL
{
	class FEnumItem final 
	{
	public:
		using FEnumNumericType = long;

		template <typename T>
		FEnumItem(const std::string& name, T value,
			const class FEnumType* EnumType)
			: m_EnumType(EnumType),
			m_Name(name),
			m_Value(static_cast<FEnumNumericType>(value)) {
		}

		auto& GetName() const noexcept { return m_Name; }

		long GetValue() const noexcept { return m_Value; }

		const class FEnumType* FEnumType() const noexcept { return m_EnumType; }

	private:
		const class FEnumType* m_EnumType;
		std::string m_Name;
		FEnumNumericType m_Value;
	};
	
	class FEnumType : public FTypeBase 
	{
	public:
		template <typename>
		friend class FEnumFactory;

		using FEnumNumericType = typename FEnumItem::FEnumNumericType;

		explicit FEnumType() : FTypeBase() {}

		explicit FEnumType(const std::string& Name, DefaultConstructFn Fn)
			: FTypeBase(Name, Fn) {
		}

		long GetValue(const FAny& Elem) const { return *(long*)(Elem.GetPayload()); }

		void SetValue(FAny& Elem, FEnumNumericType Value) const {
			if (!SET_VALUE_CHECK(Elem, EValueKind::Enum)) {
				return;
			}
			*(long*)(Elem.GetPayload()) = Value;
		}

		auto& GetEnums() const noexcept { return m_Items; }

	private:
		std::vector<FEnumItem> m_Items;

		template <typename T>
		void Add(const std::string& Name, T value) {
			m_Items.emplace_back(Name, value, this);
		}
	};
}

