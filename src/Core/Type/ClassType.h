
#pragma once
#include "Core/Core.h"
#include "Type.h"
#include "Core/Any.hpp"
#include "./Property/Property.h"

namespace REFL
{
	class FAny;
	class ClassType final : public FType
	{
		public:
			template <typename T>
			friend class FClassFactory;

			using DefaultConstructFn = FAny(void);

			explicit ClassType(const std::string& Name, DefaultConstructFn Fn)
				: FType(EValueKind::Class, Name, Fn)
			{}

			ClassType() : FType(EValueKind::Class, nullptr) {}

			auto& Properties() const noexcept { return m_Properties; }

			void SetValue(FAny& From, FAny& To);
			void StealValue(FAny& From, FAny& To);

		private:
			std::vector<Ref<FProperty>> m_Properties;
	};
}