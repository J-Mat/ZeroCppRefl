#pragma once
#include "Any.hpp"
#include "./Utils/Misc.hpp"

namespace REFL
{
	template <typename T>
	FAny MakeCopyAny(T&& Value) noexcept(
    std::is_rvalue_reference_v<T&&>
        ? std::is_nothrow_move_constructible_v<Utils::TRemoveCVRef<T>>
        : std::is_nothrow_copy_constructible_v<Utils::TRemoveCVRef<T>>) {
    using Type = Utils::TRemoveCVRef<T>;

    void* Element = nullptr;
    try {
        if constexpr (std::is_enum_v<T>) 
		{
            Element = new long{static_cast<long>(value)};
        } else 
		{
            Element = new Type{std::forward<T>(Value)};
        }
    } catch (const std::bad_alloc&) 
	{
        Element = nullptr;
    } catch (...) {
        throw;
    }
    return {TAny::EAccessType::Copy, elem, &type_operation_traits<type>::get_operations(),
            typeinfo<util::remove_cvref_t<T>>()};
}	
}