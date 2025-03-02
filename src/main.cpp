#include <iostream>
#include "Core/Reflection.h"
#include <cassert>
#include <string>

enum class TestEnum 
{
	Value1 = 1,
	Value2 = 2,
	Value3 = 3,
};

struct Person {
	Person() = default;
	bool bTest = false;
	std::string Str = "zjm";
	int Number = 123;
	float FloatNumber = 45.5f;
	TestEnum Enum = TestEnum::Value2;
};




int main(int argc, char* argv[])
{
	auto& EnumType = REFL::FEnumFactory<TestEnum>::Instance().Register("TestEnum")
		.Add("Value1", TestEnum::Value1)
		.Add("Value2", TestEnum::Value2)
		.Add("Value3", TestEnum::Value3).GetType();

	{
		for (const auto& Item : EnumType.GetEnums())
		{
			std::cout << Item.GetName() << " " << Item.GetValue() << std::endl;
		}
	}

	auto& ClassType = REFL::FClassFactory<Person>::Instance()
		.Register("Percent")
		.Property("bTest", &Person::bTest)
		.Property("Str", &Person::Str)
		.Property("Number", &Person::Number)
		.Property("FloatNumber", &Person::FloatNumber)
		.Property("Enum", &Person::Enum)
		.GetType();

	

	std::cout << ClassType.GetName() << std::endl;
	for (auto prop : ClassType.Properties())
	{
		std::cout << prop->GetName() << std::endl;
	}
	
	Person p;

	REFL::FAny ClassAny = REFL::AnyModule::MakeRefAny(p);
	assert(ClassAny.GetAccessType() == REFL::FAny::EAccessType::Ref);
	assert(ClassAny.GetType() == REFL::FactoryModule::GetType<Person>());
	
	{
		auto BoolProp = ClassType.Properties()[0];
		REFL::FAny BoolAny = BoolProp->Call(ClassAny);
		assert(BoolAny.GetType() == REFL::FactoryModule::GetType<bool>());
		BoolProp->GetType()->AsBool()->SetValue(BoolAny, true);
		bool BoolRes = BoolAny.GetType()->AsBool()->GetValue(BoolAny);
		std::cout << BoolRes << std::endl;
	}

	{
		auto StringProp = ClassType.Properties()[1];
		REFL::FAny StringAny = StringProp->Call(ClassAny);
		assert(StringAny.GetType() == REFL::FactoryModule::GetType<std::string>());
		StringProp->GetType()->AsString()->SetValue(StringAny, "zjm--");
		std::string StringRes = StringAny.GetType()->AsString()->GetValue(StringAny);
		std::cout << StringRes << std::endl;
		std::cout << p.Str << std::endl;
	}

	{
		auto IntProp = ClassType.Properties()[2];
		REFL::FAny IntAny = IntProp->Call(ClassAny);
		assert(IntAny.GetType() == REFL::FactoryModule::GetType<int>());
		int IntRes = IntAny.GetType()->AsInteger()->GetValue<int>(IntAny);
		std::cout << IntRes << std::endl;
	}
	{
		auto FloatProp = ClassType.Properties()[3];
		REFL::FAny FloatAny = FloatProp->Call(ClassAny);
		assert(FloatAny.GetType() == REFL::FactoryModule::GetType<float>());
		int FloatRes = FloatAny.GetType()->AsFloat()->GetValue<float>(FloatAny);
		std::cout << FloatRes << std::endl;
	}
	
	return 0;
}