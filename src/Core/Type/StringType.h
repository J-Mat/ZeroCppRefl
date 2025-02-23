#pragma once
#include "Core.h"
#include "TypeBase.h"
#include "Any.h"

namespace REFL
{
	class FTypeBase;
	class FStringType : public FTypeBase
	{
	public:
		FStringType();

		virtual EValueKind GetKind() const { return EValueKind::String; }

		void SetValue(FAny&, std::string Str) const;
		std::string GetValue(const FAny&) const;

	};
}