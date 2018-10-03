#include "MyVector.h"
#include <iostream>

int main()
{
    /* code */
    MyVector<int> mv(8);

    mv.push_back(1);
    mv.push_back(2);
    mv.push_back(3);
    mv.pop_back();
    mv.push_back(4);
    mv.push_back(5);
    mv.push_back(6);
    mv.push_back(7);
    mv.push_back(8);

    mv.insert(100, 2);

    std::cout << "Begin: " << mv.begin() << std::endl;
    std::cout << "End: " << mv.end() << std::endl;
    std::cout << "Back: " << mv.back() << std::endl;
    std::cout << "Size: " << mv.size() << std::endl;

    mv.PrintVector();

    std::cout << "Place 3: " << mv[3] << std::endl;

    return 0;
}
