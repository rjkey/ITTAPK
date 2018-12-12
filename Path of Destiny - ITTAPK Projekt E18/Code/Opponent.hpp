#include "CosTypes.hpp"

class Opponent
{
public:
	
	virtual ~Opponent();;

	virtual HP getHealth() = 0;
	virtual ATT getAttack() = 0;
	virtual DEF getDefence() = 0;

	virtual void setHealth(HP) = 0;
	virtual void setAttack(ATT) = 0;
	virtual void setDefence(DEF) = 0;

	virtual void show() = 0;
	virtual void showStats() = 0;
	virtual void showInventory() = 0;

private:
	std::string heroName_;
	HP health_;
	ATT attack_;
	DEF defence_;
};