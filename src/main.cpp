#include <iostream>
#include "Core/Reflection.h"
#include <cassert>

struct Person {
	Person() = default;
	bool bTest = false;
};


int main(int argc, char* argv[])
{
	auto& ClassType = REFL::FClassFactory<Person>::Instance()
		.Register("Percent")
		.Property("bTest", &Person::bTest)
		.GetType();

	std::cout << ClassType.GetName() << std::endl;
	for (auto prop : ClassType.Properties())
	{
		std::cout << prop->GetName() << std::endl;
	}
	
	auto Prop = ClassType.Properties()[0];

	Person p;
	REFL::FAny ClassAny = REFL::AnyModule::MakeRefAny(p);
	assert(ClassAny.GetAccessType() == REFL::FAny::EAccessType::Ref);
	assert(ClassAny.GetType() == REFL::FactoryModule::GetType<Person>());
	
	REFL::FAny BoolAny  = Prop->Call(ClassAny);
	assert(BoolAny.GetType() == REFL::FactoryModule::GetType<bool>());
	
	bool aa = BoolAny.GetType()->AsBool()->GetValue(BoolAny);
	std::cout << aa << std::endl;
	

	//bool* res = REFL::TypeModule::TryCast<bool>(BoolAny);
	//std::cout << *res << std::endl;
	
	return 0;
}