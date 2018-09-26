#include <iostream>
#include "SharedPtr.h"

using namespace std;

int main() {
    cout << "Creating first sharedptr." << endl;
    SharedPtr<int> ptr1(new int(5));
    cout << "Creating second sharedptr." << endl;
    SharedPtr<int> ptr2(ptr1);

    cout << "Creating bla pointer with new value" << endl;
    SharedPtr<int> bla(new int(2));

    cout << "Assigning bla pointer to first sharedptr" << endl;
    bla = bla;
    cout << "Done assigning.";

    cout << bla.count() << endl;

    return 0;
}