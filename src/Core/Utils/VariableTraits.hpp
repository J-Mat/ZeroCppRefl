#pragma once

#include <type_traits>

namespace REFL {
namespace Utils {
	namespace Detail
	{
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
	}

	template <typename T>
	using TVariableType_t = typename Detail::TVariableType<T>::Type;


	namespace Detail
	{
		template <typename T>
		auto TVariablePointerToType(long, T*) -> T;

		template <typename Class, typename T>
		auto TVariablePointerToType(char, T Class::*) -> T;
	}  // namespace detail
	template <auto V>
	using TVariablePointerToType = decltype(Detail::TVariablePointerToType(0, V));


	namespace Detail 
	{
		template <typename T>
		struct TBasicVariableTraits 
		{
			using Type = TVariableType_t<T>;
			static constexpr bool bIsMember = std::is_member_pointer_v<T>;
		};
	}

	template <typename T>
	struct TVariableTraits;

	template <typename T>
	struct TVariableTraits<T*> : Detail::TBasicVariableTraits<T> 
	{
		using Pointer = T*;
	};
	template <typename Class, typename T>
	struct TVariableTraits<T Class::*> : Detail::TBasicVariableTraits<T Class::*>
	{
		using Pointer = T Class::*;
		using ClassType = Class;
	};


	namespace Detail 
	{
		template <auto V>
		struct TVariablePointerTraits : TVariableTraits<decltype(V)>
		{};
	}
	template <auto V>
	using TVariablePointerTraits = Detail::TVariablePointerTraits<V>;
}
}