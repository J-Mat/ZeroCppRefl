#pragma once
#include "Core.h"
#include "Type.h"
#include "Any.hpp"

namespace REFL
{
	class FBoolType : public FType
	{
	public:
		FBoolType(const std::string& Name): FType(Name){}

		EValueKind GetKind() const noexcept { return EValueKind::Boolean; }

		void SetValue(FAny&, bool) const;
		bool GetValue(const FAny&) const;

	};
} // namespace DREF