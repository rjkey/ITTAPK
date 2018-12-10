#include "Opponent.hpp"
#include <vector>
#include <variant>

class EnemyList
{
private:
    std::vector<std::variant<Opponent<Monster>, Opponent<Humanoid>>> list_;
public:
    EnemyList(/* args */);
    ~EnemyList();
};

EnemyList::EnemyList(/* args */)
{
}

EnemyList::~EnemyList()
{
}
