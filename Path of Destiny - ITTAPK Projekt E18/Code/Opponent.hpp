#ifndef OPPONENT_H
#define OPPONENT_H
#define MAX_HP 100
#define MAX_ATT 30
#define MAX_DEF 30
#define MAX_GEAR_ATT 30
#define MAX_GEAR_DEF 30
#define NUMBER_OF_OPPONENT_TYPES 4

#include "CosTypes.hpp"
#include "Gear.hpp"

class Opponent
{
private:
protected:
	std::string name_;
	HP health_;
	ATT attack_;
	DEF defence_;
	Gear<ATT> weapon_;
    Gear<DEF> armour_;

public:	
	virtual ~Opponent() = default;
	virtual std::string getName() = 0;
	virtual HP getHealth() = 0;
	virtual ATT getAttack() = 0;
	virtual DEF getDefence() = 0;

	virtual Gear<ATT> getWeapon() = 0;
	virtual Gear<DEF> getArmour() = 0;

	virtual void showStats() = 0;
};

#endif // OPPONENT_H