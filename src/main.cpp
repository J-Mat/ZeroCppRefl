#include <iostream>
#include "Core/Reflection.h"
#include <cassert>
#include <string>

struct Person {
	Person() = default;
	bool bTest = false;
	std::string Str = "zjm";
};


int main(int argc, char* argv[])
{
	auto& ClassType = REFL::FClassFactory<Person>::Instance()
		.Register("Percent")
		.Property("bTest", &Person::bTest)
		.Property("Str", &Person::Str)
		.GetType();

	std::cout << ClassType.GetName() << std::endl;
	for (auto prop : ClassType.Properties())
	{
		std::cout << prop->GetName() << std::endl;
	}
	
	auto BoolProp = ClassType.Properties()[0];
	auto StringProp = ClassType.Properties()[1];

	Person p;
	REFL::FAny ClassAny = REFL::AnyModule::MakeRefAny(p);
	assert(ClassAny.GetAccessType() == REFL::FAny::EAccessType::Ref);
	assert(ClassAny.GetType() == REFL::FactoryModule::GetType<Person>());
	
	REFL::FAny BoolAny  = BoolProp->Call(ClassAny);
	assert(BoolAny.GetType() == REFL::FactoryModule::GetType<bool>());
	
	BoolProp->GetType()->AsBool()->SetValue(BoolAny, true);
	bool BoolRes = BoolAny.GetType()->AsBool()->GetValue(BoolAny);
	std::cout << BoolRes << std::endl;
	

	REFL::FAny StringAny  = StringProp->Call(ClassAny);
	assert(StringAny.GetType() == REFL::FactoryModule::GetType<std::string>());
	
	StringProp->GetType()->AsString()->SetValue(StringAny, "zjm--");
	std::string StringRes = StringAny.GetType()->AsString()->GetValue(StringAny);
	std::cout << StringRes << std::endl;
	std::cout << p.Str << std::endl;

	//bool* res = REFL::TypeModule::TryCast<bool>(BoolAny);
	//std::cout << *res << std::endl;
	
	return 0;
}