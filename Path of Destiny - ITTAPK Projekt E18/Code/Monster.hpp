#include "CosTypes.hpp"

class Monster : public Opponent
{
private:
public:
	HP getHealth() override;
	ATT getAttack() override;
	DEF getDefence() override;
	void setHealth(HP) override;
	void setAttack(ATT) override;
	void setDefence(DEF) override;
	void show() override;
	void showStats() override;
	void showInventory() override;
};

HP Monster::getHealth()
{
}

ATT Monster::getAttack()
{
}

DEF Monster::getDefence()
{
}

void Monster::setHealth(HP)
{
}

void Monster::setAttack(ATT)
{
}

void Monster::setDefence(DEF)
{
}

void Monster::show()
{
}

void Monster::showStats()
{
}

void Monster::showInventory()
{
}