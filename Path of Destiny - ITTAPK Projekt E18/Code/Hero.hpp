




#include<iostream>
#include"CostumeTypes.hpp"

#include<string>
using namespace std;


class Hero
{    
public:
    Hero(string name, HP health, ATT attack, DEF defence);
    ~Hero();


    HP getHealth();
    ATT getAttack();
    DEF getDefence();

    void setHealth(HP);
    void setAttack(ATT);
    void setDefence(DEF);
    void show();

private:
    string heroName_;
    HP health_;
    ATT attack_;
    DEF defence_;

    list< Gear > inventory_;
    Gear weaponEquipt_;
};



Hero::Hero(string name, HP health, ATT attack, DEF defence){
    heroName_ = name;
    setHealth(health);
    setDefence(defence);
    setAttack(attack);
}

Hero::~Hero(){

}

HP Hero::getHealth(){
    return health_;
}
ATT Hero::getAttack(){
    return attack_;
}
DEF Hero::getDefence(){
    return defence_;
}


void Hero::setHealth(HP health){
    health_ = health;
}
void Hero::setAttack(ATT attack){
    attack_ = attack;
}
void Hero::setDefence(DEF defence){
    defence_ = defence;
}


void Hero::show(){
    cout << "Hero stats:\n\r" << heroName_ << "\tHP: " << health_ << "\t  Attack: " << attack_ << "\tDefence: " << defence_ << endl;
}