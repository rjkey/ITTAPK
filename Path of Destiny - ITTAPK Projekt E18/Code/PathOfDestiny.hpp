//#include "Hero.hpp"
#include "CosTypes.hpp"
#include<list>
//#include "EnemyList.hpp"
#include<variant>
#include"Location.hpp"
#include "Arena.hpp"

#include <type_traits>


// the variant to visit
using var_t = std::variant<Arena<DEF>,Arena<ATT>,Path>;
// helper type for the visitor #3
template<class T> struct always_false : std::false_type {};





class PathOfDestiny
{
private:
    /* data */
    LocationFactory locationFactory_;
    std::variant<Arena<DEF>,Arena<ATT>,Path> currentLocation_;
    std::variant<Arena<DEF>,Arena<ATT>,Path> newLocation_;
 //   Hero hero; 

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
    // start with a random path. 
    currentLocation_ = locationFactory_.createPath();
}

PathOfDestiny::~PathOfDestiny()
{
}

void PathOfDestiny::gameLogic()
{
           // present location 
       // currentLocation_.show(); // use a visitor
       //if (std::holds_alternative<Arena>(currentLocation_)) {
           /* code */
           // Combat call !??! 
           // get a path to move on from - as current location
       //}

        // show possible directions
        // await player input 
        // handle input
            // if valid 
            //  get location/arena
            // if unvalid 
            //  display it, await new input
        // change gear??


        // make visit here. for currentlocation maybe 3. method could work. 


        // 2. value-returning visitor, demonstrates the idiom of returning another variant
        //var_t w = std::visit([](auto&& arg) -> var_t {return arg;}, currentLocation_);
 
        // 3. type-matching visitor: a lambda that handles each type differently
        std::cout << "Visiting currentLocation";
        std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, Arena<DEF>>)
                std::cout << "Arena DEF with value " << arg.getCombatModifier() << '\n';
            else if constexpr (std::is_same_v<T, Arena<ATT>>)
                std::cout << "Arena ATT with value " << arg.getCombatModifier() << '\n';
            else if constexpr (std::is_same_v<T, Path>){
                std::cout << "PATH with directions " << arg.getDirectionsToGo() << '\n';
            }
            else 
                static_assert(always_false<T>::value, "non-exhaustive visitor!");
        }, currentLocation_);
        //*/
}

void PathOfDestiny::movement()
{

    /*  Chris Debugging   Not working
    char input;
    int ways;
    cout<< "Choose the path to follow, using first letter in posible ways" ; 
    cin >> input;
    // 2. value-returning visitor, demonstrates the idiom of returning another variant
    var_t w = std::visit([](auto&& arg) -> var_t {return arg;}, currentLocation_);

    // 3. type-matching visitor: to return posible ways.
    std::visit([](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, Path>){
            return arg.getValue();
        }
        else if constexpr (std::is_same_v<T, Arena<DEF>>)
            cout << "Something wrong PathOfDestiny Line 110";//Do nothing
        else if constexpr (std::is_same_v<T, Arena<ATT>>)
            cout << "Something wrong PathOfDestiny Line 110";//Do nothing
        else 
            static_assert(always_false<T>::value, "non-exhaustive visitor!");
    }, w);
    





    if (ways == 0) {
        
        switch (input)
        {
            case 'l':
                cout << "Moving Left";
                break;
            case 'a':
                cout << "Moving forward";
            default:
                cout << "invalid input";
                break;
        }
    }
    else if (ways == 1) {
       
    }
    else if (ways == 2) {
       
    }
    else if (ways == 3) {
       
    }   
//*/
        // this work
        // 3. type-matching visitor: a lambda that handles each type differently
        std::cout << "Visiting currentLocation";
        std::visit([](auto&& arg) {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, Arena<DEF>>)
                std::cout << "Arena DEF with value " << arg.getCombatModifier() << '\n';
            else if constexpr (std::is_same_v<T, Arena<ATT>>)
                std::cout << "Arena ATT with value " << arg.getCombatModifier() << '\n';
            else if constexpr (std::is_same_v<T, Path>){
                std::cout << "PATH with directions " << arg.getDirectionsToGo() << '\n';
            }
            else 
                static_assert(always_false<T>::value, "non-exhaustive visitor!");
        }, currentLocation_);//*/


        // 0 for Arena else Path
        if((rand() % 2)<1) {
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
}