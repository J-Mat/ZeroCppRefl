#pragma once
#include "Core.h"
#include "TypeBase.h"
#include "Any.h"
#include "CastOp.hpp"

namespace REFL
{
	class FTypeBase;
	class FFloatType : public FTypeBase
	{
	public:
		enum EFloatKind
		{
			Unknown,
			Float,
			Double,
		};
		FFloatType(std::string Name, EFloatKind IntergerKind);
	
		EFloatKind GetFloatKind() const { return m_Kind; }

		virtual EValueKind GetTypeKind() const { return EValueKind::Float; }


		void SetValue(FAny& Any, float Value) const;
		void SetValue(FAny& Any, double Value) const;

		template <typename T>
		static FFloatType Create() { return { GetNameByType<T>(), GetFloatKindByType<T>()}; }
		


		template <typename T>
		T GetValue (FAny& Any) const 
		{
			return *TryCastConst<T>(Any);
		}

	private:
		enum EFloatKind m_Kind;

		template <typename T>
		static enum EFloatKind GetFloatKindByType() 
		{
			if constexpr (std::is_same_v<int, T>) {
				return EFloatKind::Float;
			}
			if constexpr (std::is_same_v<char, T>) {
				return EFloatKind::Double;
			}

			return Unknown;
		}


		template <typename T>
		static std::string GetNameByType() 
		{
			if constexpr (std::is_same_v<float, T>) {
				return "float";
			}
			if constexpr (std::is_same_v<double, T>) {
				return "double";
			}
			return "unknown-Float-type";
		}
	};
}