#include "SharedPtr.h"
#include <iostream>
#include <string>

class Entity
{
public:
	Entity() : Entity("")
	{
	}

	Entity(std::string name)
	{
		std::cout << "Entity created with name: " << name << std::endl;
		name_ = name;
	}

	~Entity()
	{
		std::cout << "Entity destroyed with name: " << name_ << std::endl;
	}

private:
	std::string name_;
};


int main()
{
	// Exercise 1 Making a basic shared pointer. test.

	// Default contructor
	auto pointer1(SharedPtr<Entity>(new Entity("e1")));
	auto pointer2(SharedPtr<Entity>(new Entity("e2")));
	
	// Copy constructor
	auto pointer3 = pointer1;

	// Assignment operator
	pointer2 = pointer1;
	pointer1 = pointer1;

	// Default constructor with other type
	auto pointer4(SharedPtr<int>(new int(1)));

	std::cout << *pointer4 << std::endl;
	

	// Exercise 2

	SharedPtr <std::string > sp(new std::string("Hello world"));
	if (sp)
	{
		std::cout << "SP Contains: " << *sp << std::endl;
	}

	std::cout << "Are the pointer1 and pointer3 equal?" << std::endl;
	pointer1 == pointer3 ? std::cout << "Pointers are equal." << std::endl : std::cout << "Pointers are not equal." << std::endl;

	std::cout << "Are the pointer1 and pointer2 equal?" << std::endl;
	pointer1 == pointer2 ? std::cout << "Pointers are equal." << std::endl : std::cout << "Pointers are not equal." << std::endl;
	
	std::cin.get();
}