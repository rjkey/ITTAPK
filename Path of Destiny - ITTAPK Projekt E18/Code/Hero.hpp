#ifndef HERO_HPP
#define HERO_HPP

#include<iostream>
#include"CosTypes.hpp"

#include<string>
using namespace std;
#include<list>
#include <variant>

// add/remove all gear related
#define gear



class Hero
{    
public:
    Hero();
    Hero(string name, HP health, ATT attack, DEF defence);
    ~Hero();


    HP getHealth();
    ATT getAttack();
    DEF getDefence();

    void setHealth(HP);
    void setAttack(ATT);
    void setDefence(DEF);

    #ifdef gear///////////////////////////////////////////////////////////////////
    // Create a variant to make it possible to store Gear of type ATT or DEF
    using GearVariant = std::variant< Gear<ATT>, Gear<DEF> >;
    void addGearToInventory(GearVariant);
    void changeGear(GearVariant);
    #endif //gear

    void show();
    void showStats();
    void showInventory();

private:
    string heroName_;
    HP health_;
    ATT attack_;
    DEF defence_;

    #ifdef gear///////////////////////////////////////////////////////////////////
    // Create list for inventore ATT og DEF items
    std::list< GearVariant > inventoryList_;

    // Swaps with items from inventory_
    Gear<ATT> weapon_;
    Gear<DEF> armour_;
    #endif //gear
};

Hero::Hero(){
    heroName_ = "NoName";
    health_ = 0;
    attack_ = 0;
    defence_ = 0;
}

Hero::Hero(string name, HP health, ATT attack, DEF defence){
    heroName_ = name;
    setHealth(health);
    setAttack(attack);
    setDefence(defence);

    // initiere med intet gear!
    #ifdef gear///////////////////////////////////////////////////////////////////
    Gear<ATT> unarmed("unarmed", 0);
    Gear<DEF> noAmour("no amour", 0);
    changeGear(unarmed);
    changeGear(noAmour);
    #endif //gear
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


#ifdef gear///////////////////////////////////////////////////////////////////
//template <typename Tgear>
void Hero::addGearToInventory(GearVariant Tgear){
    inventoryList_.push_back(Tgear);
}
/*/ Make ATT and DEF object and isert in list
Gear<ATT> axe("axe", 40);
Gear<DEF> shield("sheild", 20);
inventoryList_.push_back(axe);
inventoryList_.push_back(shield);*/


//template <typename Tgear>
void Hero::changeGear(GearVariant Tgear){
    /*
    if( std::holds_alternative<ATT>(Tgear)){
        swap(Tgear, weapon_)
    }
    else if( std::holds_alternative<DEF>(Tgear)){
        swap(Tgear, weapon_)
    }
    else{
        assert()
        std::cout << "Error: file=Hero.hpp function=ChangeGear()" << std::endl;
    }//*/
}
#endif //gear








void Hero::show(){
    showStats();
}
void Hero::showStats(){
    cout << "Hero stats: " << heroName_ << "\n\rHP: " << health_ << "\t  Attack: " << attack_ << "\tDefence: " << defence_ << endl;
}

#ifdef gear///////////////////////////////////////////////////////////////////
void Hero::showInventory(){
    // Make iterate point to begining and incerement it one by one till it reaches the end of list.
    for (auto it = inventoryList_.begin(); it != inventoryList_.end(); it++)
    {	
        //Print the contents
        // it->printGear(); må man ikke i variant, anvend visitor!

        // Missing Ostream operator in Gear
        //std::visit([](auto&& gear_obj){std::cout << gear_obj;}, *it);

        // Uses Gear's printfunktion, nice!
        // Visit access Variant = Gear Object, we use Lambda to call the specific printfunction for the object! 
        std::visit([](auto&& gear_obj){gear_obj.printGear();}, *it);
    }
}
#endif //gear





#endif //HERO_HPP







/*
// the variant to visit
using var_t = std::variant<int, long, double, std::string>;
 
// helper type for the visitor #3
template<class T> struct always_false : std::false_type {};
 
// helper type for the visitor #4
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;
 
int main() {
    std::vector<var_t> vec = {10, 15l, 1.5, "hello"};
    for(auto& v: vec) {
 
        // 1. void visitor, only called for side-effects (here, for I/O)
        std::visit([](auto&& arg){std::cout << arg;}, v);
 
        // 2. value-returning visitor, demonstrates the idiom of returning another variant
        var_t w = std::visit([](auto&& arg) -> var_t {return arg + arg;}, v);
 
        // 3. type-matching visitor: a lambda that handles each type differently
        std::cout << ". After doubling, variant holds ";
        std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, int>)
                std::cout << "int with value " << arg << '\n';
            else if constexpr (std::is_same_v<T, long>)
                std::cout << "long with value " << arg << '\n';
            else if constexpr (std::is_same_v<T, double>)
                std::cout << "double with value " << arg << '\n';
            else if constexpr (std::is_same_v<T, std::string>)
                std::cout << "std::string with value " << std::quoted(arg) << '\n';
            else 
                static_assert(always_false<T>::value, "non-exhaustive visitor!");
        }, w);
    }
 
    for (auto& v: vec) {
        // 4. another type-matching visitor: a class with 3 overloaded operator()'s
        std::visit(overloaded {
            [](auto arg) { std::cout << arg << ' '; },
            [](double arg) { std::cout << std::fixed << arg << ' '; },
            [](const std::string& arg) { std::cout << std::quoted(arg) << ' '; },
        }, v);
    }
}

//*/