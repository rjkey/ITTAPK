#ifndef LOCATIONFACTORY_HPP 
#define LOCATIONFACTORY_HPP
#include <string>
#include "Arena.hpp"
#include "Path.hpp"
#include "CosTypes.hpp"



static std::string arenaStrings[] = {"foggy swamps", "hills", "forrest clearing", "marketplace"};
static std::string pathStrings[] = {"forrest path", "forrest road", "hilly road", "open road"};
static int posibleArenas = 4; // Amount of elements in ArenaStrings
static int posiblePaths = 4; // Amount of elements in pathStrings



class LocationFactory
{
private:
    /* no data */
public:
    LocationFactory();
    ~LocationFactory();
    template<typename S>
    Arena<S> createArena(S combatMod);
    Path createPath();
    
};


LocationFactory::LocationFactory()
{
}


LocationFactory::~LocationFactory()
{
}

template<typename S>
Arena<S> LocationFactory::createArena(S combatMod)
{
    // creates a random name for the location from the list arenaStrings
    int nameIndex = rand() % posibleArenas; 
    std::string name = arenaStrings[nameIndex];
    Arena newArena = Arena(name, combatMod);
    //std::cout<< "made an Arena: "<< newArena<< "\n";
    return newArena;   
}

Path LocationFactory::createPath()
{
    // creates a random name for the location from the list pathStrings
    int nameIndex = rand() % posiblePaths; 
    std::string name = pathStrings[nameIndex];

    // Only 4 posible combinations of directions.
    int directions = rand() % 4; 
    Path newPath = Path(name, directions);
    
    //std::cout<< "made an path: "<< newPath<< "\n";
    return newPath; 
}

#endif // LOCATIONFACTORY_HPP