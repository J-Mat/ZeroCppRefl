#pragma once
#include "Core.h"
#include "../Type.h"
#include "../ClassType.h"

namespace REFL
{
	class FClassType;
	class FProperty : public FType
	{
	public:
		FProperty(const std::string& Name, const FClassType* owner, EQualifier q)
			: FType(Name, nullptr), m_Owner(owner), m_Qualifier(q) {}


		virtual ~FProperty() = default;

		virtual EValueKind GetKind() const {return EValueKind::Class;}
		auto GetOwner() const noexcept { return m_Owner; }

		bool IsConst() const noexcept {
			return static_cast<long>(m_Qualifier) &
				static_cast<long>(EQualifier::Const);
		}

		bool IsRef() const noexcept {
			return static_cast<long>(m_Qualifier) &
				static_cast<long>(EQualifier::Ref);
		}

		virtual const FType* GetType() const noexcept = 0;


	private:
		const FClassType* m_Owner;
		EQualifier m_Qualifier = EQualifier::None;
	};
}