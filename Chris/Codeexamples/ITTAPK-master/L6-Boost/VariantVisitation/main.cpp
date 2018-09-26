#include <iostream>
#include <boost/variant.hpp>

int main() {
    std::cout << "Hello, World!" << std::endl;
    boost::variant<int, std::string> hello(2);

    std::cout << hello << std::endl;

    hello = "Hehe";

    std::cout << hello << std::endl;

    std::string &n = boost::get<std::string>(hello);
    return 0;
}