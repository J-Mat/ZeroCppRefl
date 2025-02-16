#pragma once
#include "VariableTraits.hpp"

namespace REFL
{
	struct FTypeOperations final {
		using DestroyFn = void(void*);
		using CopyConstructFn = void*(void*);
		using StealConstructFn = void*(void*);
		using CopyAssignmentFn = void(void*, void*);
		using StealAssignmentFn = void(void*, void*);
	
		DestroyFn* destroy = empty_destroy;
		CopyConstructFn* copy_construct = empty_copy;
		StealConstructFn* steal_construct = empty_steal;
		CopyAssignmentFn* copy_assignment = empty_copy_assign;
		StealAssignmentFn* steal_assignment = empty_steal_assign;
	
		static FTypeOperations Null;
	
	private:
		static void empty_destroy(void*) {}
		static void* empty_copy(void*) { return nullptr; }
		static void* empty_steal(void*) { return nullptr; }
		static void empty_copy_assign(void*, void*) {}
		static void empty_steal_assign(void*, void*) {}
	};


	template <typename T>
	struct TTypeOperationTraits {
    static void Destroy(void* elem) 
	{
        if constexpr (std::is_destructible_v<T>) 
		{
            if constexpr (std::is_array_v<T>)
			{
                delete[] (T*)(elem);
            }
			else
			{
                delete (T*)(elem);
            }
        } else {
        }
    }

    static void* CopyConstruct(void* elem)
	{
        if constexpr (std::is_copy_constructible_v<T>)
		{
            return new T{*(const T*)elem};
        } else 
		{
            return nullptr;
        }
    }

    static void* StealConstruct(void* elem) {
        if constexpr (std::is_move_constructible_v<T>)
		{
            return new T{std::move(*(T*)elem)};
        } else
		 {
            return nullptr;
        }
    }

    static void CopyAssignment(void* Dst, void* Src) {
        if constexpr (std::is_copy_assignable_v<T>) 
		{
            *(T*)(Dst) = *(const T*)(Src);
        } else {
        }
    }

    static void StealAssignment(void* dst, void* src) {
        if constexpr (std::is_move_assignable_v<T>) 
		{
            *(T*)(dst) = std::move(*(T*)(src));
        } 
		else 
		{
        }
    }

    static auto& GetOperations() 
	{
        using Traits = TTypeOperationTraits<T>;

        static FTypeOperations Operations = {
            Traits::Destroy, Traits::CopyConstruct, Traits::StealConstruct,
            Traits::CopyAssignment, Traits::StealAssignment
		};
        return Operations;
    }
};

}