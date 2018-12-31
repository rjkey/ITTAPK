

#include <time.h>
//#include "Location.hpp"
#include "PathOfDestiny.hpp"
//#include "Arena.hpp"
//#include "Path.hpp"


int main()
{ 
    std::string name;
    // Init rand to be more random. 
    srand (time(NULL));

    std::cout << "Welcome to Path of Destiny\nName your hero: ";
    Hero hero( name, (HP)200, (ATT)15, (DEF)15);
    PathOfDestiny game = PathOfDestiny();
    std::cout << "Game start: \n"; 


    for(size_t i = 0; i < 3; i++)
    {
        //game.movement();
        game.gameLogic();
    }
    //*/
   
  
 

    return 0;
}

