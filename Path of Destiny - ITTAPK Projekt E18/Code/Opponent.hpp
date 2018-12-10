#include "Monster.hpp"
#include "Humanoid.hpp"

template<typename T>
class Opponent
{
public:
	Opponent(T opponent)
	{
		opponent_ = opponent;
	}

	T get_opponent()
	{
		return opponent_;
	}

private:
	T opponent_;
};