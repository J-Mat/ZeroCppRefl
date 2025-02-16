#pragma once
#include "Core.h"
#include "Property.h"
#include "../Type.h"
#include "../ClassType.h"
#include "Core/Factory.hpp"


namespace REFL
{
	class FBooleanProperty : public FProperty
	{
	public:
		FBooleanProperty(const std::string& Name, const ClassType* Owner, EQualifier q)
			: FProperty(name, Owner, q),
			m_Type(&FbooleanF::instance().info()) {}


		const struct FType* GetType() const noexcept override {
			return m_Type;
		}

	private:
		const FBoolType* m_Type;
	};
}