#pragma once

#include <type_traits>

namespace REFL {
namespace Utils {
	namespace Detail {
		template <typename T>
		struct TVariableType 
		{
			using Type = T;
		};

		template <typename Class, typename T>
		struct TVariableType<T Class::*> 
		{
			using Type = T;
		};

		template <typename T>
		struct TBasicVariableTraits 
		{
			using Type = TVariableType<T>;
			static constexpr bool bIsMember = std::is_member_pointer_v<T>;
		};

		template <auto V>
		struct TVariablePointerTraits : TVariableTraits<decltype(V)> 
		{};
	}

	template <typename T>
	using TVariableType_t = typename Detail::TVariableType<T>::type;

	template <typename T>
	struct TVariableTraits : Detail::TBasicVariableTraits<T> {
		using pointer = T*;
	};


	template <typename Class, typename T>
	struct TVariableTraits<T Class::*> : Detail::TBasicVariableTraits<T Class::*> {
		using Pointer = T Class::*;
		using Clazz = Class;
	};

	template <auto V>
	using TVariablePointerTraits = Detail::TVariablePointerTraits<V>;
}
}