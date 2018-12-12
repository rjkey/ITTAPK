#include "CosTypes.hpp"

class Humanoid : public Opponent
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

HP Humanoid::getHealth()
{
}

ATT Humanoid::getAttack()
{
}

DEF Humanoid::getDefence()
{
}

void Humanoid::setHealth(HP)
{
}

void Humanoid::setAttack(ATT)
{
}

void Humanoid::setDefence(DEF)
{
}

void Humanoid::show()
{
}

void Humanoid::showStats()
{
}

void Humanoid::showInventory()
{
}