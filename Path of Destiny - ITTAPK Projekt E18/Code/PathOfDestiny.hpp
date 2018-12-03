#include "Hero.hpp"
#include "CostumeTypes.hpp"
#include<list>
//#include "EnemyList.hpp"
#include<variant>
#include "Arena.hpp"
#include "Path.hpp"

class PathOfDestiny
{
private:
    /* data */

    std::variant<Arena,Path> currentLocation_, newLocation_;

public:
    PathOfDestiny(std::variant<Arena,Path> currentLocation);

    ~PathOfDestiny();
    void movement(Hero hero,list<std::variant<Arena, Path>> listLocation);
    // combat skal være overlaod. viriadic er mere til recursiv kald af function.
    
};

PathOfDestiny::PathOfDestiny(std::variant<Arena,Path> currentLocation)
 : currentLocation_(currentLocation)
{
    
}

PathOfDestiny::~PathOfDestiny()
{
}


void PathOfDestiny::movement(Hero hero, list<std::variant<Arena, Path>> listLocation)
{
       
       if (std::holds_alternative<Arena>(currentLocation_)) {
           /* code */
           // Combat call !??! 
           // get a path to move on from - as current location
       }



       
}