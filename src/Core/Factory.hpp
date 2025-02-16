#pragma once
#include "Core.h"
#include "Type/Type.h"
#include "Type/BoolType.h"

namespace REFL
{
	class FTypeDict final
	{
		public:
			static auto& Instance() {
				static FTypeDict Inst;
				return Inst;
			}

			void Add(const FType* Type) 
			{
				if (Type && !Type->GetName().empty()) 
				{
					m_TypeMap.insert_or_assign(Type->GetName(), Type);
				}
			}

			const FType* Find(std::string_view Name) 
			{
				if (auto it = m_TypeMap.find(Name); it != m_TypeMap.end())  
				{
					return it->second;
				}
				return nullptr;
			}

			auto& GetTypeMap() const noexcept { return m_TypeMap; }

		private:
			std::unordered_map<std::string_view, const FType*> m_TypeMap;

			FTypeDict() = default;
	};


	class FBooleanFactory final
	{
	public:
		static auto& Instance() noexcept
		{
			static FBooleanFactory Inst;
			return Inst;
		}

		auto& GetType() const noexcept { return m_Type; }

	private:
			FBooleanFactory() = default;
			FBoolType m_Type;
	};


	template <typename T>
	class FTypeFactory final 
	{
	public:
		static const FType* GetType() noexcept 
		{
			if constexpr (std::is_same_v<bool, T>) {
				return &FBooleanFactory::Instance().GetType()
			}
			return nullptr;
		}
	};


	template <typename T>
	class FClassFactory final {
	public:
		static auto& Instance() noexcept 
		{
			static FClassFactory inst;

			static bool bInited = false;
			if (!bInited) 
			{
				bInited = true;
				if constexpr (std::is_default_constructible_v<T>) 
				{
					inst.info_.default_construct_ = default_construct;
				}
				FTypeDict::Instance().Add(&inst.info_);
			}

			return inst;
		}

    auto& regist(const std::string& name,
                 std::vector<attribute_t>&& attrs = {}) {
        info_.name_ = name;
        info_.set_attr(std::move(attrs));

        if (!type_dict::instance().find(name)) {
            type_dict::instance().add(&info_);
        } else {
            MIRROW_LOG("type " + name + "already registered");
        }

        return *this;
    }

    template <typename U>
    auto& property(const std::string& name, U accessor, std::vector<attribute_t>&& attrs = {}) {
        using traits = util::variable_traits<U>;
        using type = typename traits::type;

        info_.properties_.emplace_back(
            property_factory{}.create(name, accessor));
        info_.properties_.back()->set_attr(std::move(attrs));

        return *this;
    }

    auto& info() const noexcept { return info_; }

	private:
		clazz info_;

		class_factory() = default;

		static any default_construct() {
			if constexpr (std::is_default_constructible_v<T>) {
				return any{any::access_type::Copy, new T{},
						&type_operation_traits<T>::get_operations(),
						&class_factory<T>::instance().info()};
			} else {
				return {};
			}
		}
	};

	template <typename T>
	const FType* GetType() 
	{
		auto Type = FTypeFactory<T>::GetType();

		if (!Type) {
			//Type = &class_factory<T>::instance().info();
		}

		return Type;
	}
}