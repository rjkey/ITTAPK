#include <iostream>

class Test { /* Some code */ };

template <typename T, int N>
class MyArray
{
    public:
    T& operator[](int i){
        return data_[i];
    }

    private:
    T data_[N];
};

 /* Using */
int main(int argc, char const *argv[])
{
    MyArray <Test , 10> my;
    
    Test t;
    my[5] = t;

    std::cout << &my[5] << std::endl;

    return 0;
}