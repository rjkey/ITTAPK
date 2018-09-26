#include <iostream>
#include "Vector.h"

template<typename T>
void printVector(my::Vector<T> &vector);

int main() {
    my::Vector<int> vec;
    for (int i = 1; i < 8; i++) {
        vec.push_back(i);
    }

    for (auto ptr : vec) {
        std::cout << ptr << std::endl;
    }

    my::Vector<char> stringVec;
    for (int i = 65; i < 70; i++) {
        stringVec.push_back(i);
    }

    printVector(stringVec);

    my::Vector<int> otherIntVec(20);
    otherIntVec = vec;

    std::cout << "Printing otherIntVec..." << std::endl;

    printVector(otherIntVec);

    return 0;
}

template<typename T>
void printVector(my::Vector<T> &vector) {
    for (auto ptr : vector) {
        std::cout << ptr << std::endl;
    }
}