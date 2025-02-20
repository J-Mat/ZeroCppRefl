#pragma once
#include "Core.h"
#include "TypeBase.h"
#include "Any.h"

namespace REFL
{
	class FTypeBase;
	class FBoolType : public FTypeBase
	{
	public:
		FBoolType();

		virtual EValueKind GetKind() const { return EValueKind::Boolean; }

		void SetValue(FAny&, bool) const;
		bool GetValue(const FAny&) const;

	};
}