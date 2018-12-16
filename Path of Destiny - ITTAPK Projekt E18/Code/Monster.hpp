#ifndef MONSTER_H
#define MONSTER_H

#include "Opponent.hpp"

class Monster : public Opponent
{
public:
    Monster();
    ~Monster();

	HP getHealth() override;
	ATT getAttack() override;
	DEF getDefence() override;

	void setHealth(HP health) override;
	void setAttack(ATT attack) override;
	void setDefence(DEF defence) override;

	void show() override;
	void showStats() override;
	void showInventory() override;
    friend std::ostream& operator<<(std::ostream& os, const Monster& M_Obj);
};

Monster::Monster()
{    
    //set health, attack and defence
}

Monster::~Monster()
{
}

HP Monster::getHealth()
{
    return health_;
}

ATT Monster::getAttack()
{
    return attack_;
}

DEF Monster::getDefence()
{
    return defence_;
}

void Monster::setHealth(HP health)
{
    health_ = health;
}

void Monster::setAttack(ATT attack)
{
    attack_ = attack;
}

void Monster::setDefence(DEF defence)
{
    defence_ = defence;
}

void Monster::show()
{
}

void Monster::showStats()
{
    std::cout << *this << std::endl;
}

void Monster::showInventory()
{
}

std::ostream& operator<<(std::ostream& os, const Monster &M_Obj)
{
    return os << M_Obj.name_ << " (" << M_Obj.health_ << M_Obj.attack_ << M_Obj.defence_ << ")";
}

#endif // MONSTER_H