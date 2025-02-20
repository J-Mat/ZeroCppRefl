#pragma once
#include "Utils/VariableTraits.hpp"

namespace REFL
{
	class FTypeOperations final 
    {
    public:
		using FDestroyFn = void(void*);
		using FCopyConstructFn = void*(void*);
		using FStealConstructFn = void*(void*);
		using FCopyAssignmentFn = void(void*, void*);
		using FStealAssignmentFn = void(void*, void*);

		FDestroyFn* Destroy = EmptyDestroy;
		FCopyConstructFn* CopyConstruct = EmptyCopy;
		FStealConstructFn* StealConstruct = EmptySteal;
		FCopyAssignmentFn* CopyAssignment = EmptyCopyAssign;
		FStealAssignmentFn* StealAssignment = EmptyStealAssign;

        FTypeOperations() = default;
        FTypeOperations(
            FDestroyFn* DestroyFn,
            FCopyConstructFn* CopyConstructFn,
            FStealConstructFn* StealConstructFn,
            FCopyAssignmentFn* CopyAssignmentFn,
            FStealAssignmentFn* StealAssignmentFn
        ) : Destroy(DestroyFn),
            CopyConstruct(CopyConstructFn),
            StealConstruct(StealConstructFn),
            CopyAssignment(CopyAssignmentFn),
            StealAssignment(StealAssignmentFn)
        {}
	private:
		static void EmptyDestroy(void*) {}
		static void* EmptyCopy(void*) { return nullptr; }
		static void* EmptySteal(void*) { return nullptr; }
		static void EmptyCopyAssign(void*, void*) {}
		static void EmptyStealAssign(void*, void*) {}
    public:
        static FTypeOperations* NullPtr()
        {
            static FTypeOperations Inst;
            return &Inst;
        }
	};

	template <typename T>
	struct TTypeOperationTraits 
    {
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

        static void* CopyConstruct(void* Elem)
        {
            if constexpr (std::is_copy_constructible_v<T>)
            {
                return new T{*(const T*)Elem};
            } else
            {
                return nullptr;
            }
        }

        static void* StealConstruct(void* Elem) {
            if constexpr (std::is_move_constructible_v<T>)
            {
                return new T{std::move(*(T*)Elem)};
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