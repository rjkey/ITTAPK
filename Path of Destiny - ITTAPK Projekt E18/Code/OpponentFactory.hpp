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
	OpponentFactory();
	~OpponentFactory();
	static std::unique_ptr<Opponent> get_opponent(int i);
};

OpponentFactory::OpponentFactory()
{
}

OpponentFactory::~OpponentFactory()
{
}

std::unique_ptr<Opponent> OpponentFactory::get_opponent(int i)
{
	switch (i)
	{
	case 0:
		return std::make_unique<Monster>();
	case 1:
		return std::make_unique<Humanoid>();
	default:
		return nullptr;
	}
}

#endif // OPPONENTFACTORY_H