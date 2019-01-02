#ifndef PATHOFDESTINY_HPP
#define PATHOFDESTINY_HPP

#include "Hero.hpp"
#include "Location.hpp"
#include "OpponentFactory.hpp"
#include "action.hpp"
#include <variant>
#include <assert.h>
#include <functional> 


// the variant to visit
using var_t = std::variant<Arena<DEF>,Arena<ATT>,Path>;
// helper type for the visitor #3
template<class T> struct always_false : std::false_type {};


class PathOfDestiny
{
private:
    LocationFactory locationFactory_;
    OpponentFactory opponentFactory_;
    std::variant<Arena<DEF>,Arena<ATT>,Path> currentLocation_;
    std::variant<Arena<DEF>,Arena<ATT>,Path> newLocation_;
    Hero hero_; 

public:
    PathOfDestiny();
    PathOfDestiny(Hero hero);

    ~PathOfDestiny();
    void gameLogic();
    void movement();    
};

PathOfDestiny::PathOfDestiny()
{
    locationFactory_ = LocationFactory();
    opponentFactory_ = OpponentFactory();
    // start with a random path. 
    currentLocation_ = locationFactory_.createPath();
}

PathOfDestiny::PathOfDestiny(Hero hero)
: hero_(hero)
{
    locationFactory_ = LocationFactory();
    opponentFactory_ = OpponentFactory();
    // start with a random path. 
    currentLocation_ = locationFactory_.createPath();
}

PathOfDestiny::~PathOfDestiny()
{
}

void PathOfDestiny::gameLogic()
{   
    //For some reation the binds copies the hero into combat instead og a reference
    auto combatDEF = std::bind(static_cast<void(*)(Arena<DEF>, std::unique_ptr<Opponent>, Hero&)>(action::combat),std::placeholders::_1, std::placeholders::_2, hero_);
    // can catch [&] [this] 
    auto combatATT = [&hero = this->hero_](Arena<ATT> arena, std::unique_ptr<Opponent> enemy){action::combat(arena, std::move(enemy), hero);};
    bool combatDone = false;
 
    
    // 3. type-matching visitor: a lambda that handles each type differently with a return boolean
    //std::cout << "Visiting currentLocation \n";
    combatDone = std::visit([&combatDEF, &combatATT, &enemyFactory = this->opponentFactory_, &hero = this->hero_](auto&& arg) -> bool {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, Arena<DEF>>){
            std::cout << arg << '\n';
            action::combat(arg,std::move(enemyFactory.getOpponent()),hero);//combatDEF(arg,std::move(enemyFactory.getOpponent()));// 
            return true;
        }
        else if constexpr (std::is_same_v<T, Arena<ATT>>){
            std::cout << arg << '\n';
            action::combat(arg,std::move(enemyFactory.getOpponent()),hero);//combatATT(arg,enemyFactory.getOpponent());
            return true;
        }
        else if constexpr (std::is_same_v<T, Path>){
            //Do nothing Path is presented later.
            //std::cout << arg << '\n';
            return false;
        }
        else 
            static_assert(always_false<T>::value, "non-exhaustive visitor!\n");
    }, currentLocation_);

    // Need a Path after combat to move on. 
    if(combatDone) {
        currentLocation_= locationFactory_.createPath();
    }
    
    movement();
    

    //*/
}

void PathOfDestiny::movement()
{
    char input; 
    int ways;
    bool validInput = false;

    std::cout << "Want to change gear? y/n  "; 
    std::cin >> input;
    
    if (input=='y') {
        int item;
        if (hero_.showInventory()) {
            std::cout << "Choose item number to use: ";
            std::cin >> item;
            hero_.changeGear(item);
        }       
    }
    
    // 3. type-matching visitor: to return posible ways.
    ways = std::visit([](auto&& arg) -> int {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, Path>){
            arg.show();
            return arg.getValue();
        }
        else 
        {
            // must be assert since input is decided runtime, if not Path = plz fail!
            assert(true);
            std::cout << "ERROR PathOfDestiny::movement - Not Path in currentlocation!\n";
            return 0;
        }
    }, currentLocation_);
    

    do{
        std::cout<< "Choose the path to follow, using first letter in the posible ways: " ; 
        std::cin >> input;
        if (ways == 0) {
            
            switch (input)
            {
                case 'l':
                    std::cout << "moving Left" << std::endl;
                    validInput = true;
                    break;
                case 'a':
                    std::cout << "moving forward"<< std::endl;
                    validInput = true;
                    break;
                default:
                    std::cout << "invalid input, try again"<< std::endl;
                    break;
            }
        }
        else if (ways == 1) {
            switch (input)
            {
                case 'r':
                    std::cout << "moving right"<< std::endl;
                    validInput = true;
                    break;
                case 'a':
                    std::cout << "moving forward"<< std::endl;
                    validInput = true;
                    break;
                default:
                    std::cout << "invalid input, try again"<< std::endl;
                    break;
            }
        }
        else if (ways == 2) {
            switch (input)
            {
                case 'l':
                    std::cout << "moving Left"<< std::endl;
                    validInput = true;
                    break;
                case 'r':
                    std::cout << "moving right"<< std::endl;
                    validInput = true;
                    break;
                default:
                    std::cout << "invalid input, try again"<< std::endl;
                    break;
            }
        }
        else if (ways == 3) {
            switch (input)
            {
                case 'l':
                    std::cout << "moving Left "<< std::endl;
                    validInput = true;
                    break;
                case 'r':
                    std::cout << "moving right "<< std::endl;
                    validInput = true;
                    break;
                case 'a':
                    std::cout << "moving forward "<< std::endl;
                    validInput = true;
                    break;
                default:
                    std::cout << "invalid input, try again"<< std::endl;
                    break;
            }
        }   
    }while(!validInput);
    //*/ 
        // 0 or 1 for Arena else Path
        if((rand() % 3)<2) {
            int value = rand() % 11 -5; // combatModifier between -5,5 
            // If negative it a DEF modifier
            if (value<1) {
                DEF combatMod = value;
                newLocation_ = locationFactory_.createArena(combatMod);
            }
            else // If positive an ATT modifier
            {
                ATT combatMod = value;
                newLocation_ = locationFactory_.createArena(combatMod);
            }           
        }
        else
        {
            newLocation_ = locationFactory_.createPath(); 
        }
    currentLocation_ = newLocation_;
       //*/
} // Working movement


#endif // PATHOFDESTINY_HPP