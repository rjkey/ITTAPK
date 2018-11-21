#include <variant>
#include <iostream>
#include "Gear.h"
//#include "Gear.h"

/*
template<int t>
struct Weapon
{
	int value = t;
};

template<int t>
struct Armor
{
	int value = t;
};
*/

int main()
{
	Gear<Armor, uint> d(new Armor, 30);
	std::cout << "Hello" << std::endl;
	return 0;
}
