#ifndef ACTION_HPP
#define ACTION_HPP

#include "Hero.hpp"
#include "Location.hpp"
#include "Opponent.hpp"
#include <memory>
#include <future> 
#include <thread>



namespace action
{
    void combat(Arena<DEF> Arena, std::unique_ptr<Opponent> enemy, Hero& hero);
    void combat(Arena<ATT> Arena, std::unique_ptr<Opponent> enemy, Hero& hero);
} // action


void action::combat(Arena<DEF> arena, std::unique_ptr<Opponent> enemy, Hero& hero){
    
    DEF dmg; 
    int i = 0;
    std::cout << "You encountered a " << enemy->getName() << "!\n\r";
    hero.show();
    enemy->show();

    do{
        // enemy attacks hero. future from an async()
        
        try
        {
            std::future<DEF> f2 = std::async(std::launch::async, [&hero, &arena, &enemy]{ return hero.getDefence() + arena.getCombatModifier() - enemy->getAttack(); });
            // hero attacks enemy.
            dmg = enemy->getDefence() - hero.getAttack();
            //std::cout << "dmg to enemy is: " << dmg<< std::endl; 
            if ( dmg < (DEF) 0) {
                enemy->setHealth((enemy->getHealth() + dmg));
            }
            f2.wait(); // If not done waiting to get done
            dmg = f2.get();
            if ( dmg < (DEF) 0) {
                hero.setHealth((hero.getHealth() + dmg));
            }
        }
        catch(const std::future_error& e)
        {
            std::cerr << "DEF combat future making \n"<< e.what() << '\n';
        }
         
        
        std::cout << ++i <<": "<< hero.getName()<< " Health: " << hero.getHealth() <<"\t"<< enemy->getName() << " Health: "<< enemy->getHealth()<< std::endl; 
    }while( !(hero.getHealth() < (HP)1) && !(enemy->getHealth() < (HP)1) );

    
    if (hero.getHealth()<1) {
        std::cout<< "The "<< enemy->getName()<< " killed you\n !!! GAME OVER !!!" ;
        exit(0);
    }
    
    // Dropped gear from monster 
    int value = rand() % 21 -10; // combatModifier between -10,10 
    // If negative it an armour
    if (value<1) {
        DEF v = (DEF) abs(value);
        Gear<DEF> newGear = Gear(v);
        std::cout << "You killed the "<< enemy->getName()<< " and found a " << newGear << " and puts it into your inventory\n";
        hero.addGearToInventory(newGear);
    }
    else // If positive a weapon
    {
        ATT v = value;
        Gear<ATT> newGear = Gear(v);
        std::cout << "You killed the "<< enemy->getName()<< " and found a " << newGear << " and puts it into your inventory\n";
        hero.addGearToInventory(newGear);
    }        
}




void action::combat(Arena<ATT> arena, std::unique_ptr<Opponent> enemy , Hero& hero){
    DEF dmg; 
    int i = 0;
    std::cout << "You encountered a" << enemy->getName() << "!\n\r";
    hero.show();
    enemy->show();
    do{
        // enemy attacks hero. 
        dmg =  hero.getDefence() - enemy->getAttack();
        if ( dmg < (DEF) 0) {
            hero.setHealth((hero.getHealth() + dmg));
        }
        // hero attacks enemy.
        dmg = enemy->getDefence() - (hero.getAttack() + arena.getCombatModifier());  
        if ( dmg < (DEF) 0) {
            enemy->setHealth((enemy->getHealth() + dmg));
        }
        std::cout << ": " << ++i << hero.getName()<< " Health: " << hero.getHealth() <<"\t"<< enemy->getName() << " Health: "<< enemy->getHealth()<< std::endl; 
    }while( !(hero.getHealth() < (HP)1) && !(enemy->getHealth() < (HP)1)  );

    if (hero.getHealth()<1) {
        std::cout<< "The "<< enemy->getName()<< " killed you\n !!! GAME OVER !!!\n\n" ;
        exit(0);
    }
    
    // Dropped gear from monster 
    int value = rand() % 21 -10; // combatModifier between -10,10 
    // If negative it an armour
    if (value<1) {
        DEF v = abs(value);
        Gear<DEF> newGear = Gear(v);
        std::cout << "You found a " << newGear << " and puts it into your inventory\n";
        hero.addGearToInventory(newGear);
    }
    else // If positive a weapon
    {
        ATT v = value;
        Gear<ATT> newGear = Gear(v);
        std::cout << "You found a " << newGear << " and puts it into your inventory\n";
        hero.addGearToInventory(newGear);
    }         
}

#endif // ACTION_HPP