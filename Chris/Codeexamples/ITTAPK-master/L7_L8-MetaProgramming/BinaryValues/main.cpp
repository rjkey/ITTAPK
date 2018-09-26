#include <iostream>

template<size_t N>
struct NotABinaryNumber;

template<>
struct NotABinaryNumber<0>
{
    enum { value = 0 };
};

template<>
struct NotABinaryNumber<1>
{
    enum { value = 1 };
};

template<size_t N>
struct Binary {
    static const size_t value = Binary<N / 10>::value << 1 | NotABinaryNumber<N % 10>::value;
};

template<>
struct Binary<0> {
    static const size_t value = 0;
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    Binary<5> kage;

    std::cout << Binary<1100120>::value << std::endl;
    return 0;
}