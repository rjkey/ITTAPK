

#include <time.h>
#include "Location.hpp"
#include "PathOfDestiny.hpp"
//#include "Arena.hpp"
//#include "Path.hpp"


int main()
{
   

  
    // Init rand to be more random. 
    srand (time(NULL));

    PathOfDestiny game = PathOfDestiny();
    cout << "Game start: \n"; 


    for(size_t i = 0; i < 10; i++)
    {
        //game.movement();
        game.gameLogic();
    }
    //*/
   
  
 

    return 0;
}

