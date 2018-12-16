#ifndef OPPONENT_H
#define OPPONENT_H

#include "CosTypes.hpp"
#include "Gear.hpp"

class Opponent
{
private:
	std::string name_;
	HP health_;
	ATT attack_;
	DEF defence_;
	Gear<ATT> weapon_;
    Gear<DEF> armour_;

public:	
	virtual ~Opponent() = default;
	virtual HP getHealth() = 0;
	virtual ATT getAttack() = 0;
	virtual DEF getDefence() = 0;
	virtual void setHealth(HP) = 0;
	virtual void setAttack(ATT) = 0;
	virtual void setDefence(DEF) = 0;
	virtual void show() = 0;
	virtual void showStats() = 0;
	virtual void showInventory() = 0;
};

#endif // OPPONENT_H