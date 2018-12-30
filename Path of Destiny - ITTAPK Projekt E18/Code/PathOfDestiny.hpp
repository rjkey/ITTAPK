

#include "Hero.hpp"
#include "CosTypes.hpp"
#include<list>
#include<variant>
#include"Location.hpp"
//#include "Arena.hpp"

#include <type_traits>
#include <functional> 


// the variant to visit
using var_t = std::variant<Arena<DEF>,Arena<ATT>,Path>;
// helper type for the visitor #3
template<class T> struct always_false : std::false_type {};


namespace action
{
    void combat(Arena<DEF> Arena, Hero hero);
    void combat(Arena<ATT> Arena, Hero hero);
} // action




class PathOfDestiny
{
private:
    /* data */
    LocationFactory locationFactory_;
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
    // start with a random path. 
    currentLocation_ = locationFactory_.createPath();
}

PathOfDestiny::~PathOfDestiny()
{
}

void PathOfDestiny::gameLogic()
{   
    auto combatDEF = std::bind(static_cast<void(*)(Arena<DEF>, Hero)>(action::combat),std::placeholders::_1, hero_);
    // kan gribes med [&] [this] 
    auto combatATT = [&hero = this->hero_](Arena<ATT> arena){action::combat(arena, hero);};
    bool combatDone = false;
        
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
 

    // 2. value-returning visitor, demonstrates the idiom of returning another variant
    //var_t w = std::visit([](auto&& arg) -> var_t {return arg;}, currentLocation_);

    // 3. type-matching visitor: a lambda that handles each type differently
    //std::cout << "Visiting currentLocation \n";
    combatDone = std::visit([&combatDEF, &combatATT](auto&& arg) -> bool {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, Arena<DEF>>){
            std::cout << "Arena DEF with value " << arg.getCombatModifier() << '\n';
            combatDEF(arg);
            return true;
        }
        else if constexpr (std::is_same_v<T, Arena<ATT>>){
            std::cout << "Arena ATT with value " << arg.getCombatModifier() << '\n';
            combatATT(arg);
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
    if (combatDone) {
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

void action::combat(Arena<DEF> arena, Hero hero){
    cout << "Entered DEF combat with Hero: " << hero << "in the arena " << arena << std::endl;
}

void action::combat(Arena<ATT> arena, Hero hero){
    cout << "Entered ATT combat with Hero: " << hero << "in the arena " << arena << std::endl;
}