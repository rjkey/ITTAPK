#include <iostream>

int counter = 0;

template<typename T> T GetSumOfArgs(T args) {
  std::cout << __PRETTY_FUNCTION__ <<  "\n" << "Args: " << args << std::endl;
  return args;
}

template <typename T, typename... Args> T GetSumOfArgs(T firstArg, Args... args){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    counter++;
    return firstArg + GetSumOfArgs(args...);
}

int main()
{
    long sum = GetSumOfArgs(1, 3, 4, 100, 2, 3, 4, 5, 1000);

    std::cout << "Sum of args: " << sum << std::endl;
    std::cout << "Counter: " << counter << std::endl;

    return 0;
}