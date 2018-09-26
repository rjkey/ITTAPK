#include <iostream>
#include "MyArray.h"

using namespace std;

template <typename T, typename V>
T* myfind(T* first , T* last , const V& v) {
    T* retValue = last;
    for (; first != last; first++) {
        if (*first == v)
            retValue = first;
    }
    return retValue;
}

int main() {
    MyArray<int, 10> myArray;
    cout << myArray.size() << endl;
    myArray.fill(5);
    cout << myArray[2] << endl;
    myArray[4] = 25;
    cout << myArray[4] << endl;
    myArray[8] = 3;

    cout << "Looking for '3'? " << (myfind(myArray.begin(), myArray.end(), 3) != myArray.end() ? "found " : "sry no") << endl;

    MyArray<double, 10> myArray1;
    myArray1.fill(10);
    myArray1[2] = 3;

    cout << "Looking for '3' in double array?" <<
         (myfind(myArray1.begin(), myArray1.end(), 3) != myArray1.end() ? "found" : "sry no") << endl;

    MyArray<int, 10> array1;
    array1.fill(2);
    MyArray<double, 10> array2(array1);
    for (auto iter: array2) {
        cout << iter << endl;
    }

    return 0;
}