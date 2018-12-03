#include <iostream>
#include <string>
#include "CostumeTypes.hpp"

using namespace std;

class Monster
{
private:
    string name_;
    ATT attack_;
    DEF defence_;
    HP health_;

public:
    Monster(string name, ATT attack, DEF defence, HP health);
    Monster();
    ~Monster();
    string getName();
    void setName(string name);
    ATT getAttack();
    void setAttack(ATT attack);
    DEF getDefence();
    void setDefence(DEF defence);
    HP getHealth();
    void setHealth(HP health);
    void show() const ;
};

Monster::Monster(string name, ATT attack, DEF defence, HP health)
{
    name_ = name;
    attack_ = attack;
    defence_ = defence; 
    health_ = health;
}

Monster::Monster()
{
    name_ = "Unknown";
    attack_ = 0;
    defence_ = 0;
    health_ = 0; 
}

Monster::~Monster()
{
}

string Monster::getName()
{
    return name_;
}

void Monster::setName(string name)
{
    name_ = name;
}

ATT Monster::getAttack()
{
    return attack_;
}

void Monster::setAttack(ATT attack)
{
    attack_ = attack; 
}

DEF Monster::getDefence()
{
    return defence_; 
}

void Monster::setDefence(DEF defence)
{
    defence_ = defence;
}

HP Monster::getHealth()
{
    return health_;
}

void Monster::setHealth(HP health)
{
    health_ = health;
}

void Monster::show() const
{
    cout << name_<< " health: "<< health_ << " attack: "<< attack_ << " defence: " << defence_ << endl;
}