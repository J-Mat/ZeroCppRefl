#include <iostream>
#include <variable_traits.hpp>

struct Person {
	Person() = default;
	std::string name;
	float height;
	const bool hasChild;
	const Person* couple;
};




int main(int argc, char *argv[])
{
	Person kk();
	auto test = &Person::height;	
	variable_traits<decltype(&Person::height)>::return_type a;
	variable_traits<decltype(&Person::height)>::class_type b();
	a = 4.0f;
	std::cout << a << std::endl;
	return 0;
}