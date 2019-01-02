#ifndef OPPONENTFACTORY_H
#define OPPONENTFACTORY_H

#include <memory>
#include "Opponent.hpp"
#include "Monster.hpp"
#include "Humanoid.hpp"


class OpponentFactory
{
private:
	/* data */
public:
	OpponentFactory(); //Default constructor
	~OpponentFactory();

	//Method using Unique ptr (smartpointer)
	static std::unique_ptr<Opponent> getOpponent();
};

OpponentFactory::OpponentFactory()
{
}

OpponentFactory::~OpponentFactory()
{
}

std::unique_ptr<Opponent> OpponentFactory::getOpponent() 
{
	int i = rand() % 2;
	switch (i)
	{
	case 0:
		try{
			return std::make_unique<Monster>();
		}
		catch(std::bad_alloc& ba){
			std::cerr << "Bad allocation caught in OpponentFactory. " << ba.what() << '\n'; 
		}		
		
	case 1:
		try{
			return std::make_unique<Humanoid>();
		}
		catch(std::bad_alloc& ba){
			std::cerr << "Bad allocation caught in OpponentFactory. " << ba.what() << '\n'; 
		}

	default:
		return nullptr;
	}
}

#endif // OPPONENTFACTORY_H