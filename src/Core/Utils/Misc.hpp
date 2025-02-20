#pragma once
#include "../Core.h"

namespace REFL {
namespace Utils {
	namespace Detail
	{
		template <typename T>
		struct IsString {
			static constexpr bool bValue = false;
		};

		template <>
		struct IsString<std::string> {
			static constexpr bool bValue = true;
		};

		template <typename T>
		struct IsStdArray {
			static constexpr bool bValue = false;
		};

		template <typename T, size_t N>
		struct IsStdArray<std::array<T, N>> {
			static constexpr bool bValue = true;
		};


		template <typename T>
		struct IsVector {
			static constexpr bool bValue = false;
		};

		template <typename T>
		struct IsVector<std::vector<T>> {
			static constexpr bool bValue = true;
		};


		template <typename T>
		struct IsMap {
			static constexpr bool bValue = false;
		};

		template <typename K, typename V>
		struct IsMap<std::map<K, V>> {
			static constexpr bool bValue = true;
		};
	}
	template <typename T>
	using TRemoveCVRef = std::remove_cv_t<std::remove_reference_t<T>>;

	template <typename T>
	constexpr bool bIsStdArray = Detail::is_std_array<T>::Value;

	template <typename T>
	constexpr bool bIsVector = Detail::IsVector<T>::value;


	template <typename T>
	constexpr bool IsMap = Detail::IsMap<T>::Value;


	template <typename T>
	constexpr bool IsString = Detail::IsString<T>::Value;
}
}