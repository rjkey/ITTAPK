#ifndef PATHOFDESTINY_HPP
#define PATHOFDESTINY_HPP

#include "Hero.hpp"
//#include "CosTypes.hpp"
#include "Location.hpp"
#include "OpponentFactory.hpp"
#include <list>
#include <variant>
#include <assert.h>
#include <functional> 


// the variant to visit
using var_t = std::variant<Arena<DEF>,Arena<ATT>,Path>;
// helper type for the visitor #3
template<class T> struct always_false : std::false_type {};


namespace action
{
    void combat(Arena<DEF> Arena, std::unique_ptr<Opponent> enemy, Hero hero);
    void combat(Arena<ATT> Arena, std::unique_ptr<Opponent> enemy, Hero hero);
} // action




class PathOfDestiny
{
private:
    /* data */
    LocationFactory locationFactory_;
    OpponentFactory opponentFactory_;
    std::variant<Arena<DEF>,Arena<ATT>,Path> currentLocation_;
    std::variant<Arena<DEF>,Arena<ATT>,Path> newLocation_;
    Hero hero_; 

public:
    PathOfDestiny();

    ~PathOfDestiny();
    void gameLogic();
    void movement();
    
    // combat skal være overlaod. viriadic er mere til recursiv kald af function.
    
};

PathOfDestiny::PathOfDestiny()
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
    auto combatDEF = std::bind(static_cast<void(*)(Arena<DEF>, std::unique_ptr<Opponent>, Hero)>(action::combat),std::placeholders::_1, std::placeholders::_2, hero_);
    // kan gribes med [&] [this] 
    auto combatATT = [&hero = this->hero_](Arena<ATT> arena, std::unique_ptr<Opponent> enemy){action::combat(arena, std::move(enemy), hero);};
    bool combatDone = false;
 
    // combine 2. and 3. for return value, from variant. 
    // 2. value-returning visitor, demonstrates the idiom of returning another variant
    //var_t w = std::visit([](auto&& arg) -> var_t {return arg;}, currentLocation_);

    // 3. type-matching visitor: a lambda that handles each type differently
    //std::cout << "Visiting currentLocation \n";
    combatDone = std::visit([&combatDEF, &combatATT, &enemyFactory = this->opponentFactory_](auto&& arg) -> bool {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, Arena<DEF>>){
            std::cout << "Arena DEF with value " << arg.getCombatModifier() << '\n';
            
            combatDEF(arg,enemyFactory.get_opponent());
            return true;
        }
        else if constexpr (std::is_same_v<T, Arena<ATT>>){
            std::cout << "Arena ATT with value " << arg.getCombatModifier() << '\n';
            combatATT(arg,enemyFactory.get_opponent());
            return true;
        }
        else if constexpr (std::is_same_v<T, Path>){
            std::cout << "PATH with directions " << arg.getDirectionsToGo() << '\n';
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

    // Chris Debugging   Not working
    char input; 
    int ways;
    bool validInput = false;
    // 2. value-returning visitor, demonstrates the idiom of returning another variant
    //var_t w = std::visit([](auto&& arg) -> var_t {return arg;}, currentLocation_);

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
            cout << "ERROR PathOfDestiny::movement - Not Path in currentlocation!\n";
            return 0;
        }
    }, currentLocation_);
    

    do{
        cout<< "Choose the path to follow, using first letter in the posible ways: " ; 
        cin >> input;
        if (ways == 0) {
            
            switch (input)
            {
                case 'l':
                    cout << "moving Left" << endl;
                    validInput = true;
                    break;
                case 'a':
                    cout << "moving forward"<< endl;
                    validInput = true;
                    break;
                default:
                    cout << "invalid input, try again"<< endl;
                    break;
            }
        }
        else if (ways == 1) {
            switch (input)
            {
                case 'r':
                    cout << "moving right"<< endl;
                    validInput = true;
                    break;
                case 'a':
                    cout << "moving forward"<< endl;
                    validInput = true;
                    break;
                default:
                    cout << "invalid input, try again"<< endl;
                    break;
            }
        }
        else if (ways == 2) {
            switch (input)
            {
                case 'l':
                    cout << "moving Left"<< endl;
                    validInput = true;
                    break;
                case 'r':
                    cout << "moving right"<< endl;
                    validInput = true;
                    break;
                default:
                    cout << "invalid input, try again"<< endl;
                    break;
            }
        }
        else if (ways == 3) {
            switch (input)
            {
                case 'l':
                    cout << "moving Left "<< endl;
                    validInput = true;
                    break;
                case 'r':
                    cout << "moving right "<< endl;
                    validInput = true;
                    break;
                case 'a':
                    cout << "moving forward "<< endl;
                    validInput = true;
                    break;
                default:
                    cout << "invalid input, try again"<< endl;
                    break;
            }
        }   
    }while(!validInput);
    //*/ 


        // 0 for Arena else Path
        if((rand() % 3)<2) {
            int value = rand() % 21 -10; // combatModifier between -10,10 
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

void action::combat(Arena<DEF> arena, std::unique_ptr<Opponent> enemy, Hero hero){
    DEF dmg; 
    std::cout << "You encountered a" << enemy->getName() << "!\n\r";
    hero.showStats();
    enemy->showStats();

    do{
         // enemy attacks hero. 
        dmg =  hero.getDefence() - enemy->getAttack();
        if ( dmg < (DEF) 0) {
            hero.setHealth(hero.getHealth() + dmg);
        }
        dmg = enemy->getDefence() - hero.getAttack();


    }while( hero.getHealth() < 1 || enemy->getHealth() < 1 );
}




void action::combat(Arena<ATT> arena, std::unique_ptr<Opponent> enemy , Hero hero){
    cout << "Entered ATT combat with Hero: " << hero << "in the arena " << arena << std::endl;
}

#endif // PATHOFDESTINY_HPP