
#ifndef ARENA_HPP
#define ARENA_HPP

#include<string>
#include<iostream>
#include"CosTypes.hpp"

using namespace std;


template<typename T>
class Arena 
{
private:
    string areaName_;
    T combatmodifier_; 
public:
    Arena(string name, T combatmod );
    Arena();
    ~Arena();
    T getCombatModifier();
    void show() const ;

 friend ostream& operator<< (ostream& os, const Arena& arena)
 {
     return os << "you have entered " << arena.areaName_ << "affecting your attack with "<< arena.combatmodifier_;// << std::endl;  
     //(arena.combatmodifier_<0? " lowering " : " adding ") << 
 }
};

template<typename T>
Arena<T>::Arena(string name, T combatmod)
    :areaName_(name),combatmodifier_(combatmod)
{
}

template<typename T>
Arena<T>::Arena()
{
    areaName_ = "unknown";
    //combatmodifier_ = (ATT) 0 ; 
}

template<typename T>
Arena<T>::~Arena()
{
}

template<typename T>
T Arena<T>::getCombatModifier()
{
    return combatmodifier_; 
}

template<typename T>
void Arena<T>::show() const{

cout << "you have entered " << areaName_ << " affecting your attack with "<< combatmodifier_ << std::endl;  
     //(arena.combatmodifier_<0? " lowering " : " adding ") << 
}

#endif //ARENA_HPP