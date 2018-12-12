#include "Monster.hpp"
#include "Humanoid.hpp"

template<typename T>
class Opponent
{

public:
	Opponent();

	Opponent(T opponent);

	~Opponent();

	Opponent(const Opponent& other);

	Opponent(Opponent&& other) noexcept;

	Opponent& operator=(const Opponent& other);

	Opponent& operator=(Opponent&& other) noexcept;;

private:
	T opponent_;
};

template <typename T>
Opponent<T>::Opponent()
{
}

template <typename T>
Opponent<T>::Opponent(T opponent)
{
	opponent_ = opponent;
}

template <typename T>
Opponent<T>::~Opponent()
{
}

template <typename T>
Opponent<T>::Opponent(const Opponent& other)
{
}

template <typename T>
Opponent<T>::Opponent(Opponent&& other) noexcept
{
}

template <typename T>
Opponent<T>& Opponent<T>::operator=(const Opponent& other)
{
	return {};
}

template <typename T>
Opponent<T>& Opponent<T>::operator=(Opponent&& other) noexcept
{
	return {};
}