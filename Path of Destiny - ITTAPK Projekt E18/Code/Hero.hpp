#ifndef HERO_HPP
#define HERO_HPP

#include<iostream>
#include"CosTypes.hpp"
#include"Gear.hpp"

#include<string>
using namespace std;
#include<list>
#include <variant>
#include <utility>  // for exchange(); -see overloads



class Hero
{    
public:
    Hero();
    Hero(string name, HP health, ATT attack, DEF defence);
    ~Hero();


    HP getHealth() const;
    ATT getAttack() const;
    DEF getDefence() const;

    void setHealth(HP);
    void setAttack(ATT);
    void setDefence(DEF);

    // Create a variant to make it possible to store Gear of type ATT or DEF
    using GearVariant = std::variant< Gear<ATT>, Gear<DEF> >;
    
    void addGearToInventory(GearVariant);
    void changeGear(uint i);
    void dropGear(uint i);
    void setGear(GearVariant);

    void show();
    void showStats();
    void showInventory();

//////////////////// Overloads ////////////////////
    // Rule of 5: + Ostream (destructor above)
    /*
    Hero(const Hero& other) { // copy constructor
    heroName_ = other.heroName_;
    health_ = other.health_;
    attack_ = other.attack_;
    defence_ = other.defence_;
    inventoryList_ = other.inventoryList_;
    weapon_ = other.weapon_;
    armour_ = other.armour_;
    }//*/

    /*Hero(Hero&& other) noexcept // move constructor
        :heroName_(std::exchange(other.heroName_, nullptr)),
        health_(std::exchange(other.health_, nullptr)),
        attack_(std::exchange(other.attack_, nullptr)),
        defence_(std::exchange(other.defence_, nullptr)),
        inventoryList_(std::exchange(other.inventoryList_, nullptr)),
        weapon_(std::exchange(other.weapon_, nullptr)),
        armour_(std::exchange(other.armour_, nullptr))
    {}//*/

    /*Hero& operator=(const Hero& other) { // copy assignment
        return *this = Hero(other);
    }//*/

    /*Hero& operator=(Hero&& other) noexcept { // move assignment
        std::swap(heroName_, other.heroName_);
        std::swap(health_, other.health_);
        std::swap(attack_, other.attack_);
        std::swap(defence_, other.defence_);
        std::swap(inventoryList_, other.inventoryList_);
        std::swap(weapon_, other.weapon_);
        std::swap(armour_, other.armour_);
        return *this;
    }//*/

    friend std::ostream& operator<<(std::ostream& os, const Hero& H_Obj){ // Ostream overload

    /*/return os << "Hero stats: " << H_Obj.heroName_ << "\n\rHP: "
    << H_Obj.health_ << "\t  Attack: " << H_Obj.attack_() << "\tDefence: " << H_Obj.defence_ << "\n\r"
    << "Weapon : " << H_Obj.weapon_ << "\n\rAmour  : " << H_Obj.armour_ << endl;//*/

    // All GetFunctions() must be const for this to work
    return os << "Hero: " << H_Obj.heroName_ << "\n\rHP: "
    << H_Obj.getHealth() << "\t  Attack: " << H_Obj.getAttack() << "\tDefence: " << H_Obj.getDefence() << "\n\r"
    << "Weapon : " << H_Obj.weapon_ << "\n\rAmour  : " << H_Obj.armour_ << "\n\r";//*/
    }

//////////////////// Menbers_ ////////////////////
private:
    string heroName_;
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
}

Hero::Hero(string name, HP health, ATT attack, DEF defence){
    heroName_ = name;
    setHealth(health);
    setAttack(attack);
    setDefence(defence);

    // initiate with no gear    (could be std::optional()?? )
    Gear<ATT> unarmed("unarmed", 0);
    Gear<DEF> noAmour("no amour", 0);
    weapon_ = unarmed;
    armour_ = noAmour;
    //changeGear(unarmed);      // don't use for initialisation, swaps with a nullPtr
    //changeGear(noAmour);
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




//template<class T> struct always_false : std::false_type {};

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
        cout << "ERROR: File: Hero.hpp, Function: setGear()\n\r";
    }//*/
    
    /*
    using T = std::decay_t<decltype(VarGear)>;
    if constexpr (std::is_same_v<T, Gear<ATT> >) {
        weapon_ = std::get<Gear<ATT>>(VarGear);
        std::cout << "Change weapon to: "<< weapon_ << "\n\r";
    }
    else if constexpr (std::is_same_v<T, Gear<DEF> >) {
        armour_ = std::get<Gear<DEF>>(VarGear);
        std::cout << "Change armour to: "<< armour_ << "\n\r";
    }
    else {
        static_assert(always_false<T>::value, "ERROR: File: Hero.hpp, Function: changeGear()\n\r");
    }//*/
}




void Hero::changeGear(uint i){
    if (i<=inventoryList_.size()) {
        std::cout << "Pick item to wear: 1-" << inventoryList_.size() << "\n\r";

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
        cout << "False input\n\r";
    }
}

void Hero::dropGear(uint i) {
    if (i<=inventoryList_.size()) {
        std::cout << "Pick item to drop: 1-" << inventoryList_.size() << "\n\r";

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
        cout << "False input\n\r";
    }
}


void Hero::show(){
    // with Hero Ostream overlaod
    std::cout << *this << std::endl;

    // with Gear Ostream overload
    //showStats();
    //cout << "Weapon : " << weapon_ << "\n\rAmour  : " << armour_ << endl;

    // Old implementation
    /*cout << "Weapon : ";
    weapon_.printGear();
    cout << "Amour  : ";
    armour_.printGear();*/
}

void Hero::showStats(){
    // with Safetype Ostream overload
    cout << "Hero stats: " << heroName_ << "\n\rHP: " << health_ << "\t  Attack: " << attack_ << "\tDefence: " << defence_ << endl;
}

void Hero::showInventory(){
    std::cout << "Inventory: ";
    if (inventoryList_.size() == 0 ) {
        std::cout << "Empty";
    }
    else{
        std::cout << "\n\r";
        // Make iterate point to begining and incerement it one by one till it reaches the end of list.
        for (auto it = inventoryList_.begin(); it != inventoryList_.end(); it++)
        {	
            //Print the contents
            // it->printGear(); må man ikke i variant, anvend visitor!

            // Ostream operator in Gear implemented
            std::visit([](auto&& gear_obj){std::cout << gear_obj;}, *it);
            std::cout << "\t";

            // Uses Gear's printfunktion
            // Visit access Variant = Gear Object, we use Lambda to call the specific printfunction for the object! 
            //std::visit([](auto&& gear_obj){gear_obj.printGear();}, *it);
        }
    }
    std::cout << "\n\r";
}




#endif //HERO_HPP























/*struct Visitor{
    Visitor(ATT& V_ATT) : ATT_(V_ATT) {}
    Visitor(DEF& V_DEF) : DEF_(V_DEF) {}

    void operator()(ATT V_ATT){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << V_ATT << std::endl;
        std::swap(ATT_, V_ATT);
    };

    void operator()(DEF V_DEF){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << V_DEF << std::endl;
        std::swap(DEF_, V_DEF);
    };

    ATT& ATT_;
    DEF& DEF_;
};//*/

// helper type for the visitor #3
//template<class T> struct always_false : std::false_type {};

/*struct Visitor{
    Visitor(Gear<ATT>& V_ATT) : ATT_(V_ATT) {}
    //Visitor(Gear<DEF>& V_DEF) : DEF_(V_DEF) {}

    void operator()(Gear<ATT> V_ATT){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << V_ATT << std::endl;
        //std::swap(ATT_, V_ATT);
    }

    //void operator()(Gear<DEF> V_DEF){
    //    std::cout << __PRETTY_FUNCTION__ << std::endl;
    //    std::cout << V_DEF << std::endl;
    //    std::swap(DEF_, V_DEF);
    //}

    Gear<ATT>& ATT_;
    //Gear<DEF>& DEF_;
};//*/

/*struct Visitor{
    Visitor(Gear<ATT>& G_Obj) : to_Vari_Obj(G_Obj) {}
    //Visitor(Gear<DEF>& V_DEF) : DEF_(V_DEF) {}

    void operator()(Gear<ATT> G_Obj){
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::cout << G_Obj << std::endl;
        std::swap(to_Vari_Obj, G_Obj);
    }

    template<typename T>
    void operator()(T&&)
    {
        std::cout << "ERROR: File:var_test_temp.cpp, Function: Visitor()\n\r";
    }

    Gear<ATT>& to_Vari_Obj;
};//*/



/*void Hero::changeGear(GearVariant VarGear){
    // TJEK det rigtige kommer ind???
    //std::cout << "DEBUG test object input ATT/DEF: ";
    //std::visit([](auto&& gear_obj) { gear_obj.printGear(); }, VarGear);

    if( std::holds_alternative<Gear<ATT>>(VarGear) ){
        //std::cout << "change attack" << std::holds_alternative<Gear<ATT>>(VarGear) << std::endl;          // Type check
        std::cout << "Change weapon to: ";
        //std::visit([](auto&& gear_obj) { gear_obj.printGear(); }, VarGear);  //WORKS prints gear
        std::visit([](auto&& gear_obj){std::cout<<gear_obj<<"\n\r";}, VarGear);

        // tmp is deleted with scope
        Gear<ATT> tmp = std::get<Gear<ATT>>(VarGear);
        std::swap(tmp, weapon_);
        //VarGear = tmp;
        //std::visit([&](auto&& gear_obj) { gear_obj = tmp; }, VarGear);


        std::visit([&, tmp](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, Gear<ATT> >) {

                arg = tmp;
                //std::swap(weapon_, arg);
            }
            else if constexpr (std::is_same_v<T, Gear<DEF> >)
                std::cout << "DEF with value " << arg << '\n';
            else
                static_assert(always_false<T>::value, "ERROR: File:var_test_temp.cpp, Function: Visitor()\n\r");
        }, VarGear);

    }
    else if( std::holds_alternative<Gear<DEF>>(VarGear) ){
        //std::cout << "change defence" << std::holds_alternative<Gear<ATT>>(VarGear) << std::endl;          // Type check
        std::cout << "Change armour to: ";
        std::visit([](auto&& gear_obj){gear_obj.printGear();}, VarGear);       //prints gear
        
        Gear<DEF> tmp = std::get<Gear<DEF>>(VarGear);
        std::swap(tmp, armour_);
        VarGear = tmp;

    }
    else{
        //assert()
        std::cout << "Error: file=Hero.hpp function=ChangeGear()" << std::endl;
    }

std::cout << "\n\r";
}//*/


