
#ifndef ARENA_HPP
#define ARENA_HPP

#include<string>
#include<iostream>
#include"CosTypes.hpp"


template<typename T>
class Arena 
{
private:
    std::string areaName_;
    T combatmodifier_; 
public:
    Arena(std::string name, T combatmod );
    Arena();
    ~Arena();
    T getCombatModifier();
    void show() const ;

 friend std::ostream& operator<< (std::ostream& os, const Arena& arena)
 {
 std::cout << "you have entered " << arena.areaName_ << " affecting your stats with "<< arena.combatmodifier_ << std::endl; 
 return os;
 }
};

template<typename T>
Arena<T>::Arena(std::string name, T combatmod)
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

std::cout << "you have entered " << areaName_ << " affecting your stats with "<< combatmodifier_ << std::endl; 
}


#endif //ARENA_HPP