
#pragma once
#include "Core.h"
#include "TypeBase.h"
#include "Any.h"
#include "./Property/Property.h"

namespace REFL
{
	class FProperty;
	class FClassType final : public FTypeBase
	{
	public:
		template <typename T>
		friend class FClassFactory;

		using DefaultConstructFn = FAny(void);

		explicit FClassType(const std::string& Name, DefaultConstructFn Fn)
			: FTypeBase(Name, Fn)
		{}

		FClassType() : FTypeBase() {}

		virtual EValueKind GetKind() const { return EValueKind::Class; }

		auto& Properties() const noexcept { return m_Properties; }

		void SetValue(FAny& From, FAny& To);
		void StealValue(FAny& From, FAny& To);

	private:
		std::vector<Ref<FProperty>> m_Properties;
	};
}