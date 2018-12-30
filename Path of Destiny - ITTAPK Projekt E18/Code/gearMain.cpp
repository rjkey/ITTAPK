#include <variant>
#include <iostream>
#include "Gear.hpp"
#include "OpponentFactory.hpp"

int main()
{
	OpponentFactory of;

	auto r = of.getOpponent(1);
	r->showStats();

	return 0;
}
