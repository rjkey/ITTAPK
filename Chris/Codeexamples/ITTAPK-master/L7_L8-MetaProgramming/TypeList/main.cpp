#include <iostream>
#include "TypeList.h"

int main() {

/* Must be true */
    std::cout << "IsSame <int , int >:: value=" << IsSame<int, int>::value << std::
    endl;

/* Must be false */
    std::cout << "IsSame <int , char >:: value=" << IsSame<int, char>::value << std
    ::endl;

    // Contains
    typedef TYPELIST3(int, char, long) TL;
/* Must be true */
    std::cout << "Contains <TL , int >:: value =" << Contains<TL, int>::value << std::endl;
/* Must be false */
    std::cout << "Contains <TL , std :: string >:: value =" << Contains<TL, std::string>::value << std::endl;


    // AtIndex
    typedef TYPELIST3(long, char, int) TL2;
/* Must be true */
    std::cout << "IsSame < typename AtIndex <TL , 2>:: type , int >:: value " << IsSame<
            typename AtIndex<TL2, 2>::type, int>::value << std::endl;

    AtIndex<TL2, 5>::type myInt;

/* Must be false */
    std::cout << "IsSame < typename AtIndex <TL , 2>:: type , char >:: value " << IsSame
            <typename AtIndex<TL2, 2>::type, char>::value << std::endl;

    std::cout << "Trying to print out all types." << std::endl;

    PrintIt<TL2>::print();
    return 0;
}