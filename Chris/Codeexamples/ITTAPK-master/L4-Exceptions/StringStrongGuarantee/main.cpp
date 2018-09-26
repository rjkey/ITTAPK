
#include "String.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    my::String str("String 1!");
    my::String str2("String 2!");
    my::String str3(str);

    std::cout << str << std::endl; // String 1

    str = str2;

    std::cout << str << std::endl; // String 2

    std::cout << str3 << std::endl; // String 1git st

    return 0;
}