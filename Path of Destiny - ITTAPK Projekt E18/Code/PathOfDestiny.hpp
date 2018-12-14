//#include "Hero.hpp"
#include "CosTypes.hpp"
#include<list>
//#include "EnemyList.hpp"
#include<variant>
#include"Location.hpp"
#include "Arena.hpp"

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


void PathOfDestiny::movement()
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

        // 0 for Arena else Path
        if ((rand() % 2)<1) {
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
       
}