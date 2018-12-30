#ifndef HUMANOID_H
#define HUMANOID_H

#include "Opponent.hpp"

static std::array<std::string, NUMBER_OF_OPPONENT_TYPES> list_of_humanoids = { "Bandit", "Evil knight", "Assassin", "Evil farmer" };

class Humanoid : public Opponent
{

public:
    Humanoid();
    ~Humanoid();

    std::string getName() override;
	HP getHealth() override;
	ATT getAttack() override;
	DEF getDefence() override;

    Gear<ATT> getWeapon() override;
    Gear<DEF> getArmour() override;

	void showStats() override;
    friend std::ostream& operator<<(std::ostream& os, const Humanoid& H_Obj);
};

Humanoid::Humanoid()
{
    srand (time(0)); //seed the rand for random numbers
    name_ = list_of_humanoids[rand() % (NUMBER_OF_OPPONENT_TYPES - 1) + 0];
    health_ = rand() % MAX_HP + 1;
    attack_ = rand() % MAX_ATT + 1;
    defence_ = rand() % MAX_DEF + 1;

    Gear<ATT> weapon(rand() % MAX_GEAR_ATT + 1);
    Gear<DEF> armour(rand() % MAX_GEAR_DEF + 1);
    weapon_ = weapon;
    armour_ = armour;
}

Humanoid::~Humanoid()
{
}

std::string Humanoid::getName()
{
    return name_;
}

HP Humanoid::getHealth()
{
    return health_;
}

ATT Humanoid::getAttack()
{
    return (attack_ + weapon_.getValue());
}

DEF Humanoid::getDefence()
{
    return (defence_ + armour_.getValue());
}

Gear<ATT> Humanoid::getWeapon()
{
    return weapon_;
}

Gear<DEF> Humanoid::getArmour()
{
    return armour_;
}

void Humanoid::showStats()
{
    std::cout << *this << std::endl;
    weapon_.printGear();
    armour_.printGear();
}

std::ostream& operator<<(std::ostream& os, const Humanoid &H_Obj)
{
    return os << H_Obj.name_ << " (" << " Health: " << H_Obj.health_ << " Attack: " << H_Obj.attack_ << " Defence: " << H_Obj.defence_ << ")";
}

#endif // HUMANOID_H