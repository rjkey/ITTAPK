#ifndef GEAR_H
#define GEAR_H
#define MAX 3
#include <string>
#include <array>
#include "CosTypes.hpp"

std::array<std::string, MAX> list_of_weapons = { "Axe", "Sword", "Mace" };
std::array<std::string, MAX> list_of_armors = {"Iron armor", "Wooden armor", "Steel armor", };

template<typename T>
class Gear
{
	static_assert(std::is_same<T, ATT>::value || std::is_same<T, DEF>::value, "GEAR: invalid type");
private:
	T value_;
	std::string name_;

	static size_t random_number() {
		return rand() % (MAX - 1) + 0;
	}
public:
	Gear(T value) {
		value_ = value;
		if constexpr (std::is_same_v<T, ATT>)
		{
			name_ = list_of_weapons[random_number()];
		}
		else if(std::is_same_v<T, DEF>)
		{
			name_ = list_of_armors[random_number()];
		}
	}

	~Gear() {
	}
	void set_value(T value) {
		value_ = value;
	}
	T get_value() {
		return value_;
	}

	std::string get_name() const
	{
		return name_;
	}
	void show() {
	}
};

#endif // GEAR_H