#include <iostream>




// Opretter struct til IKKE binære numre
template <size_t N>
struct NotBinary;

// opret default template til 0 og 1
template <>
struct NotBinary <0>
{
  static const size_t value = 0;
};

template <>
struct NotBinary <1>
{
  static const size_t value = 1;
};




// opret template struct N til binary
// køre funktionen indtil binary = 0
template <size_t N>
struct Binary
{
  static const size_t value = Binary <N/10 >:: value << 1 | NotBinary<N%10>::value;
};

// end recurtion funktion
template <>
struct Binary <0>
{
  static const size_t value = 0;
};




int main(int argc, char* argv[])
{
  printf("Run\n");



std::cout << "Binary <1011>:: value = " << Binary <1021 >:: value << std::endl;
/* Should generate a compiler error , but does not! */

  
  printf("\nDone\n");
  return 0;
}