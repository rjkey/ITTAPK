#ifndef GEAR_H
#define GEAR_H

struct Weapon{};
struct Armor{};

template<typename T, typename R>
class Gear
{
public:
	Gear(T* type, R value)
	{
		static_assert(std::is_same<Weapon, T>::value || std::is_same<uint, R>::value, "FAG!");
		static_assert(std::is_same<Armor, T>::value || std::is_same<uint, R>::value, "FAG!");
		type_ = type;
		value_ = value;
	}

	~Gear() 
	{
		delete type_; 
	}

	void SetValue(uint value)
	{
		value_ = value;
	}

	R GetValue() const
	{
		return value_;
	}

private:
	T* type_;
	R value_ = 10;
};

#endif // GEAR_H
