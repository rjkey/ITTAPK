#include<string>
#include<iostream>
#include"Location.hpp"

using namespace std;

#ifndef Arena

class Arena : virtual public Location
{
private:
    string areaName_;
    int combatmodifier_; 
public:
    Arena(string name, int combatmod );
    Arena();
    ~Arena();
    int getCombatModifier();
    void show() const ;
};

Arena::Arena(string name, int combatmod){

    areaName_ = name;
    combatmodifier_ = combatmod ; 
}

Arena::Arena(){

    areaName_ = "unknown";
    combatmodifier_ = 0 ; 
}

Arena::~Arena(){


}

int Arena::getCombatModifier(){
    return combatmodifier_; 
}

void Arena::show() const{

    std::cout << "you have entered " << areaName_ << (combatmodifier_<0? " lowering " : " adding ") << "your attack with "<< combatmodifier_ << std::endl;
}


#endif