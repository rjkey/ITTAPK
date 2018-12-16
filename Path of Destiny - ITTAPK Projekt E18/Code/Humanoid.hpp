#ifndef HUMANOID_H
#define HUMANOID_H

#include "CosTypes.hpp"
#include "Opponent.hpp"

class Humanoid : public Opponent
{
private:
	std::string name_;
	HP health_;
	ATT attack_;
	DEF defence_;
    Gear<ATT> weapon_;
    Gear<DEF> armour_;

public:
    Humanoid();
    ~Humanoid();

	HP getHealth() override;
	ATT getAttack() override;
	DEF getDefence() override;

	void setHealth(HP health) override;
	void setAttack(ATT attack) override;
	void setDefence(DEF defence) override;

	void show() override;
	void showStats() override;
	void showInventory() override;
    friend std::ostream& operator<<(std::ostream& os, const Humanoid& H_Obj);
};

Humanoid::Humanoid()
{
    //set health, attack and defence
    //set weapon and armor
}

Humanoid::~Humanoid()
{
}

HP Humanoid::getHealth()
{
    return health_;
}

ATT Humanoid::getAttack()
{
    return attack_;
}

DEF Humanoid::getDefence()
{
    return defence_;
}

void Humanoid::setHealth(HP health)
{
    health_ = health;
}

void Humanoid::setAttack(ATT attack)
{
    attack_ = attack;
}

void Humanoid::setDefence(DEF defence)
{
    defence_ = defence;
}

void Humanoid::show()
{
    std::cout << *this << std::endl;
}

void Humanoid::showStats()
{
}

void Humanoid::showInventory()
{
}

std::ostream& operator<<(std::ostream& os, const Humanoid &H_Obj)
{
    return os << H_Obj.name_ << " (" << H_Obj.health_ << H_Obj.attack_ << H_Obj.defence_ << ")";
}

#endif // HUMANOID_H