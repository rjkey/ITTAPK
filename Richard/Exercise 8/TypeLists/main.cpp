#include <iostream>

#define TYPELIST1(A) TypeList<A, NullType>
#define TYPELIST2(A, B) TypeList<A, TypeList<B, NullType>>
#define TYPELIST3(A, B, C) TypeList<A, TypeList<B, TypeList<C, NullType>>>
#define TYPELIST4(A, B, C, D) TypeList<A, TypeList<B, TypeList<C, TypeList<D, NullType>>>>

struct NullType{};

template<typename L, typename R>
struct TypeList{
    typedef L First;
    typedef R Rest;
};

typedef TYPELIST1(int) OneTL;
typedef TYPELIST2(int, char) TwoTL;
typedef TYPELIST3(int, char, long) ThreeTL;
typedef TYPELIST4(char, int, long, short) FourTL;

template<typename T, typename U>
struct IsSame{
    static const bool value = false;
};

template<typename T>
struct IsSame<T, T>{
    static const bool value = true;
};

template<typename TL, typename T>
struct Contains{
    static const bool value = IsSame<typename TL::First, T>::value || Contains<typename TL::Rest, T>::value;
};

template<typename T>
struct Contains<NullType, T>{
    static const bool value = false;
};

int main(){

    /* ---- IS SAME ---- */
    /* Must be true */
    std::cout << "IsSame <int, int> ::value " << IsSame<int, int>::value << std::endl;

    /* Must be false */
    std::cout << "IsSame <int, char> ::value " << IsSame<int, char>::value << std::endl;

    /* ---- CONTAINS ---- */
    /* Must be true */
    std::cout << "Contains <TwoTL, int> ::value " << Contains<TwoTL, int>::value << std::endl;

    /* Must be false */
    std::cout << "Contains <TwoTL, long> ::value " << Contains<TwoTL, long>::value << std::endl;

    /* ---- AT INDEX ----*/
    
    return 0;
}