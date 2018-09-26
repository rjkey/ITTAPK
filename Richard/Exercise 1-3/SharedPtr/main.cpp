#include <iostream>
#include "shared_ptr.hpp"

int main(){
    std::cout << "Hello people of earth" << std::endl;

    {
        shared_ptr<int> one = new int(5);
        {
            shared_ptr<int> two = one;
        }
    }

    return 0;
}