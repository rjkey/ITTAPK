#ifndef HERO_HPP
#define HERO_HPP

#include<iostream>
#include"CosTypes.hpp"
#include"Gear.hpp"

#include<string>
#include<list>
#include <variant>



class Hero
{    
public:
    Hero();
    Hero(std::string name, HP health, ATT attack, DEF defence);
    ~Hero();


    HP getHealth() const;
    ATT getAttack() const;
    DEF getDefence() const;
    std::string getName() const;

    void setHealth(HP);
    void setAttack(ATT);
    void setDefence(DEF);

    // Create a variant to make it possible to store Gear of type ATT or DEF
    using GearVariant = std::variant< Gear<ATT>, Gear<DEF> >;
    
    void addGearToInventory(GearVariant);
    void changeGear(uint i);
    void dropGear(uint i);

    void show();
    void showStats();
    bool showInventory();

    // All GetFunctions() must be const for this to work
    friend std::ostream& operator<<(std::ostream& os, const Hero& H_Obj) {
    return os << "Hero: " << H_Obj.heroName_ 
    << "\n\rHealth: " << H_Obj.getHealth() << "\t  Attack: " << H_Obj.getAttack() << "\tDefence: " << H_Obj.getDefence() << "\n\r"
    << "Weapon : " << H_Obj.weapon_ << "\n\rAmour  : " << H_Obj.armour_ << "\n\r";
    }


private:
    void setGear(GearVariant);
    std::string heroName_;
    HP health_;
    ATT attack_;
    DEF defence_;

    // Create list for inventory ATT og DEF items
    std::list< GearVariant > inventoryList_;

    // One ATT and DEF item can be worn from inventory_
    Gear<ATT> weapon_;
    Gear<DEF> armour_;
};














/////////////////////////////////////////////
// ***** Hero Implementation ***** //
/////////////////////////////////////////////

Hero::Hero(){
    heroName_ = "NoName";
    health_ = 0;
    attack_ = 0;
    defence_ = 0;
    Gear<ATT> unarmed("unarmed", 0);
    Gear<DEF> noAmour("no amour", 0);
    weapon_ = unarmed;
    armour_ = noAmour;
}

Hero::Hero(std::string name, HP health, ATT attack, DEF defence){
    heroName_ = name;
    setHealth(health);
    setAttack(attack);
    setDefence(defence);

    Gear<ATT> unarmed("unarmed", 0);
    Gear<DEF> noAmour("no amour", 0);
    weapon_ = unarmed;
    armour_ = noAmour;
}

Hero::~Hero(){
}



HP Hero::getHealth() const {
    return health_;
}
ATT Hero::getAttack() const {
    return (attack_ + weapon_.getValue());  //returns total attack
}
DEF Hero::getDefence() const {
    return (defence_ + armour_.getValue()); //returns total defence
}
std::string Hero::getName() const{
    return heroName_;
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



void Hero::addGearToInventory(GearVariant Tgear){
    inventoryList_.push_back(Tgear);
}

void Hero::setGear(GearVariant VarGear){
    // Sets weapon/armour to passed VarGear
    if( std::holds_alternative<Gear<ATT>>(VarGear) ){
        weapon_ = std::get<Gear<ATT>>(VarGear);
        //std::cout << "Change weapon to: "<< weapon_ << "\n\r";
    }
    else if( std::holds_alternative<Gear<DEF>>(VarGear) ){
        armour_ = std::get<Gear<DEF>>(VarGear);
        //std::cout << "Change armour to: "<< armour_ << "\n\r";
    }
    else {
        std::cout << "ERROR: File: Hero.hpp, Function: setGear()\n\r";
    }//*/
}

void Hero::changeGear(uint i){
    if (i<=inventoryList_.size()) {
        //std::cout << "Pick item to wear: 1-" << inventoryList_.size() << "\n\r";

        // make iterator
        auto it = inventoryList_.begin();
        // set iterator to chosen item
        advance(it, i-1);
        // change gear
        setGear(*it);

        // display change
        std::cout << "Item picked: ";
        std::visit([](auto&& gear_obj){std::cout << gear_obj;}, *it);
        std::cout << "\n\r";
    }
    else{
        std::cout << "False input\n\r";
    }
}


void Hero::dropGear(uint i) {
    if (i<=inventoryList_.size()) {
        //std::cout << "Pick item to drop: 1-" << inventoryList_.size() << "\n\r";

        // make iterator
        auto it = inventoryList_.begin();
        // set iterator to chosen item
        advance(it, i-1);

        // if chosen gear is equiped, change to no gear
        if(std::get<Gear<ATT>>(*it) == weapon_){
            Gear<ATT> unarmed("unarmed", 0);
            weapon_ = unarmed;
        }
        else if(std::get<Gear<DEF>>(*it) == armour_){
            Gear<DEF> noAmour("no amour", 0);
            armour_ = noAmour;
        }

        // display change
        std::cout << "Item droped: ";
        std::visit([](auto&& gear_obj){std::cout << gear_obj;}, *it);
        std::cout << "\n\r";

        // erase gear from list
        inventoryList_.erase(it);
    }
    else{
        std::cout << "False input\n\r";
    }
}


void Hero::show(){
    // with Hero Ostream overlaod
    std::cout << *this << std::endl;
}

void Hero::showStats(){
    // with Safetype Ostream overload
    std::cout << "Hero stats: " << heroName_ << "\n\rHP: " << health_ << "\t  Attack: " << attack_ << "\tDefence: " << defence_ << std::endl;
}

bool Hero::showInventory(){
    std::cout << "Inventory: ";
    if (inventoryList_.size() == 0 ) {
        std::cout << "Empty\n\r";
        return false;
    }
    else{
        std::cout << "\n\r";
        int i = 1;
        // Make iterate point to begining and incerement it one by one till it reaches the end of list.
        for (auto it = inventoryList_.begin(); it != inventoryList_.end(); it++)
        {	
            //Print the contents
            // it->printGear(); må man ikke i variant, anvend visitor!

            // Ostream operator in Gear implemented
            std::cout << i++ << ": ";
            std::visit([](auto&& gear_obj){std::cout << gear_obj;}, *it);
            std::cout << "\t";

            // Uses Gear's printfunktion
            // Visit access Variant = Gear Object, we use Lambda to call the specific printfunction for the object! 
            //std::visit([](auto&& gear_obj){gear_obj.printGear();}, *it);
        }
        std::cout << "\n\r";
        return true;
    }
}









#endif //HERO_HPP




