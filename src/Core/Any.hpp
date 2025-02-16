#pragma once
#include "./Type/Type.h"
#include "OperationTrait.hpp"

namespace REFL
{
	class FAny
	{
		FAny() = default;

		enum class EAccessType {
			Null,
			ConstRef,
			Ref,
			Copy,
		};
		FAny(enum EAccessType AccessType, void* Payload, const FTypeOperations* Operations, const FType* Type)
        : m_Access(AccessType),
		m_Payload(Payload),
		m_Operations(Operations),
		m_Type(Type) 
		{}
	public:
		const FType* GeteType() const {return m_Type;}
		EAccessType GetAccessType() const {return m_Access;}
		void* GetPayload() {return m_Payload;}

	private:
		enum EAccessType m_Access = EAccessType::Null;
		void* m_Payload = nullptr;
		const FTypeOperations* m_Operations = &FTypeOperations::Null;
		const FType* m_Type = nullptr;
	};
} // namespace REFL