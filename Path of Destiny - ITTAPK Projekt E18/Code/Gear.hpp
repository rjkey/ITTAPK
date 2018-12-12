#ifndef GEAR_H
#define GEAR_H
#define MAX 3
#include <string>
#include <array>
#include "CosTypes.hpp"

std::array<std::string, MAX> list_of_weapons = { "Axe", "Sword", "Mace" };
std::array<std::string, MAX> list_of_armors = {"Iron armor", "Wooden armor", "Steel armor", };

template <typename T>
class Gear
{
	static_assert(std::is_same<T, ATT>::value || std::is_same<T, DEF>::value, "GEAR: invalid type");
public:
	Gear();
	explicit Gear(T att_def);
	~Gear();
	Gear(const Gear& other);
	Gear(Gear&& other) noexcept;
	Gear& operator=(const Gear& other);
	Gear& operator=(Gear&& other) noexcept;
	friend std::ostream& operator<<(std::ostream& os, const Gear& G_Obj);
	void printGear();
private:
	T weapon_amour_;
	std::string name_;
	static size_t random_number();
};

template <typename T>
Gear<T>::Gear()
{
}

template <typename T>
Gear<T>::Gear(T att_def)
{
	weapon_amour_ = att_def;
	
	if(std::is_same_v<T, ATT>){
		name_ = list_of_weapons[random_number()];
	} 
	else if(std::is_same_v<T, DEF>){
		name_ = list_of_armors[random_number()];
	}
}

template <typename T>
Gear<T>::~Gear()
{
}

template <typename T>
Gear<T>::Gear(const Gear& other)
{
	name_ = other.name_;
	weapon_amour_ = other.weapon_amour_;
}

template <typename T>
Gear<T>::Gear(Gear&& other) noexcept 
	: weapon_amour_(std::exchange(other.weapon_amour_, nullptr)),
	name_(std::exchange(other.name_, nullptr))
{
}

template <typename T>
Gear<T>& Gear<T>::operator=(const Gear& other)
{
	return *this = Gear(other);
}

template <typename T>
Gear<T>& Gear<T>::operator=(Gear&& other) noexcept
{
	std::swap(name_, other.name_);
	std::swap(weapon_amour_, other.weapon_amour_);
	return *this;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Gear<T> &G_Obj)
{
	return os << G_Obj.name_ << " (" << G_Obj.weapon_amour_ << ")";
}

template <typename T>
void Gear<T>::printGear()
{
	std::cout << *this << std::endl;
}

template <typename T>
size_t Gear<T>::random_number()
{
	return rand() % (MAX - 1) + 0;
}

#endif // GEAR_H