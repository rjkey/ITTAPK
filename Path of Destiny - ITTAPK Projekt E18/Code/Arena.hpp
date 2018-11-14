#include<string.h>
#include<iostream>



class Arena
{
private:
    string areaName_;
    int combatmodifier_; 
public:
    Arena(string name, int combatmod );
    ~Arena();
    int getCombatModifier();
    void show();
};

Arena::Arena(string name, int combatmod){

    areaName_ = new name;
    combatmodifier_ = combatmod ; 
}

Arena::~Arena(){


}

int Arena::getCombatModifier(){
    return combatmodifier_; 
}

void Arena::show(){

    std::cout << "you have entered " << areaName_ << (combatmodifier_<0? "lowering " : "adding ") << "your attack with "<< combatmodifier_ << std::endl;
}