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
	//Default Constructor
	Gear(){}

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

	~Gear() {}

	Gear(const Gear& other) { // copy constructor
		name_ = other.name_;
  		weapon_amour_ = other.weapon_amour_;
	}

	Gear(Gear&& other) noexcept // move constructor
  		: name_(std::exchange(other.name_, nullptr)),
    	weapon_amour_(std::exchange(other.weapon_amour_, nullptr))
	{}

	Gear& operator=(const Gear& other) { // copy assignment
      return *this = Gear(other);
	}

	Gear& operator=(Gear&& other) noexcept { // move assignment
    	std::swap(name_, other.name_);
    	std::swap(weapon_amour_, other.weapon_amour_);
    	return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Gear& G_Obj){ // Ostream overload
  		return os << G_Obj.name_ << " (" << G_Obj.weapon_amour_ << ")";
	}

	void printGear(){
		std::cout << *this << std::endl;
  }
};

#endif // GEAR_H