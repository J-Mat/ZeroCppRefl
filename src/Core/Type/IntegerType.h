#pragma once
#include "Core.h"
#include "TypeBase.h"
#include "Any.h"
#include "CastOp.hpp"

namespace REFL
{
	class FTypeBase;
	class FIntegerType : public FTypeBase
	{
	public:
		enum EIntergerKind
		{
			Unknown,
			Char,
			Int,
			Short,
			LongLong,
			Uint8,
			Uint16,
			Uint32,
			Uint64,
		};
		FIntegerType(std::string Name, EIntergerKind IntergerKind);
	
		EIntergerKind GetIntegerKind() const { return m_Kind; }

		virtual EValueKind GetTypeKind() const { return EValueKind::Integer; }


		void SetValue(FAny& Any, long Value) const;
		void SetValue(FAny& Any, uint64_t Value) const;

		template <typename T>
		static FIntegerType Create() { return { GetNameByType<T>(), GetIntegerKindByType<T>()}; }
		


		template <typename T>
		T GetValue (FAny& Any) const 
		{
			return *TryCastConst<T>(Any);
		}

	private:
		enum EIntergerKind m_Kind;

		template <typename T>
		static enum EIntergerKind GetIntegerKindByType() 
		{
			if constexpr (std::is_same_v<int, T>) {
				return EIntergerKind::Int;
			}
			if constexpr (std::is_same_v<char, T>) {
				return EIntergerKind::Char;
			}
			if constexpr (std::is_same_v<short, T>) {
				return EIntergerKind::Short;
			}
			if constexpr (std::is_same_v<long long, T>) {
				return EIntergerKind::LongLong;
			}
			if constexpr (std::is_same_v<uint8_t, T>) {
				return EIntergerKind::Uint8;
			}
			if constexpr (std::is_same_v<uint16_t, T>) {
				return EIntergerKind::Uint16;
			}
			if constexpr (std::is_same_v<uint32_t, T>) {
				return EIntergerKind::Uint32;
			}
			if constexpr (std::is_same_v<uint64_t, T>) {
				return EIntergerKind::Uint64;
			}

			return Unknown;
		}


		template <typename T>
		static std::string GetNameByType() 
		{
			if constexpr (std::is_same_v<int, T>) {
				return "int";
			}
			if constexpr (std::is_same_v<char, T>) {
				return "char";
			}
			if constexpr (std::is_same_v<short, T>) {
				return "short";
			}
			if constexpr (std::is_same_v<long long, T>) {
				return "long long";
			}
			if constexpr (std::is_same_v<uint8_t, T>) {
				return "uint8";
			}
			if constexpr (std::is_same_v<uint16_t, T>) {
				return "uint16";
			}
			if constexpr (std::is_same_v<uint32_t, T>) {
				return "uint32";
			}
			if constexpr (std::is_same_v<uint64_t, T>) {
				return "uint64";
			}
			return "unknown-integer-type";
		}
	};
}