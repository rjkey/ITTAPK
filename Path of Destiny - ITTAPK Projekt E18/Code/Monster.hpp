#ifndef MONSTER_H
#define MONSTER_H

#include "Opponent.hpp"

static std::array<std::string, NUMBER_OF_OPPONENT_TYPES> list_of_monsters = { "Werewolf", "Troll", "Grizzly bear", "Warthog" };

class Monster : public Opponent
{
public:
    Monster();
    ~Monster();

    std::string getName() override;
	HP getHealth() override;
	ATT getAttack() override;
	DEF getDefence() override;

    Gear<ATT> getWeapon() override;
    Gear<DEF> getArmour() override;

	void showStats() override;
    friend std::ostream& operator<<(std::ostream& os, const Monster& M_Obj);
};

Monster::Monster()
{
    srand (time(0)); //seed the rand for random numbers
    name_ = list_of_monsters[rand() % (NUMBER_OF_OPPONENT_TYPES - 1) + 0]; 
    health_ = rand() % MAX_HP + 1;
    attack_ = rand() % MAX_ATT + 1;
    defence_ = rand() % MAX_DEF + 1;
}

Monster::~Monster()
{
}

std::string Monster::getName()
{
    return name_;
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

Gear<ATT> Monster::getWeapon()
{
    return weapon_;
}

Gear<DEF> Monster::getArmour()
{
    return armour_;
}

void Monster::showStats()
{
    std::cout << *this << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Monster &M_Obj)
{
    return os << M_Obj.name_ << " (" << " Health: " << M_Obj.health_ << " Attack: " << M_Obj.attack_ << " Defence: " << M_Obj.defence_ << ")";
}

#endif // MONSTER_H