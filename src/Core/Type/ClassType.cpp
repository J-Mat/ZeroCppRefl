#include "ClassType.h"
#include "OperationTrait.hpp"

namespace REFL
{
	void FClassType::SetValue(FAny& From, FAny& To)
	{
		if (!COPY_VALUE_CHECK(From, EValueKind::Class) ||
        !SET_VALUE_CHECK(To, EValueKind::Class))
		{
			return;
		}
		if (From.GetType() != To.GetType())
		{
			return;
		}
		To.GetOperations()->CopyAssignment(To.GetPayload(), From.GetPayload());
	}

	void FClassType::StealValue(FAny& From, FAny& To)
	{
		if (!COPY_VALUE_CHECK(From, EValueKind::Class) ||
        !SET_VALUE_CHECK(To, EValueKind::Class))
		{
			return;
		}
		if (From.GetType() != To.GetType())
		{
			return;
		}
		To.GetOperations()->StealAssignment(To.GetPayload(), From.GetPayload());
	}
}