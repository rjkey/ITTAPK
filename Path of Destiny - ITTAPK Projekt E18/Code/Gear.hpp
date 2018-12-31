#ifndef GEAR_H
#define GEAR_H
#define MAX 4
#include <string>
#include <array>
#include "CosTypes.hpp"

static std::array<std::string, MAX> list_of_weapons = { "Axe", "Sword", "Mace", "Knife" };
static std::array<std::string, MAX> list_of_armors = {"Shield", "Helmet", "Chestplate", "Chainmail"};

template <typename T>
class Gear
{
	static_assert(std::is_same<T, ATT>::value || std::is_same<T, DEF>::value, "GEAR: invalid type");
public:
	// Constructors
	Gear();
	explicit Gear(T att_def);
	explicit Gear (std::string name, T att_def);
	~Gear();

	// Overloads
	Gear(const Gear& other);
	Gear(Gear&& other) noexcept;
	Gear& operator=(const Gear& other);
	Gear& operator=(Gear&& other) noexcept;
	friend std::ostream& operator<<(std::ostream& os, const Gear& G_Obj)
	{
		return os << G_Obj.name_ << " (" << G_Obj.weapon_amour_ << ")";
	}

	// Logic operations
	template<class Rhs, std::enable_if_t<!std::is_same<Rhs, Gear>{},int> =0 >
	friend bool operator==(Rhs const& ptr, Gear) {
	return !*ptr;
	}

	template<class Rhs, std::enable_if_t<!std::is_same<Rhs, Gear>{},int> =0 >
	friend bool operator!=(Rhs const& ptr, Gear) {
	return !(ptr==Gear{});
	}

	template<class Lhs, std::enable_if_t<!std::is_same<Lhs, Gear>{},int> =0 >
	friend bool operator==(Gear, Lhs const& ptr) {
	return !*ptr;
	}

	template<class Lhs, std::enable_if_t<!std::is_same<Lhs, Gear>{},int> =0 >
	friend bool operator!=(Gear, Lhs const& ptr) {
	return !(Gear{}==ptr);
	}

	friend bool operator==(Gear, Gear) {
	return true;
	}

	friend bool operator!=(Gear, Gear) {
	return false;
	}//*/


	// Functions
	T getValue() const;
	void printGear();

private:
	T weapon_amour_;
	std::string name_;
	static size_t random_number();
};




// Constructors
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
Gear<T>::Gear (std::string name, T att_def){
		weapon_amour_ = att_def;
		name_ = name;
	}

template <typename T>
Gear<T>::~Gear()
{
}

// Overloads
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



// Functions
template <typename T>
void Gear<T>::printGear()
{
	std::cout << *this << std::endl;
}

template <typename T>
T Gear<T>::getValue() const
{
	return weapon_amour_;
}

template <typename T>
size_t Gear<T>::random_number()
{
	//srand (time(0)); // placed in main 
	return rand() % (MAX - 1) + 0;
}

#endif // GEAR_H