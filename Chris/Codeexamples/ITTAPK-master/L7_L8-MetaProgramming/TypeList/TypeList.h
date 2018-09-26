#ifndef TYPELIST_TYPELIST_H
#define TYPELIST_TYPELIST_H

#include <iostream>
#include <type_traits>
#include <typeinfo>

struct NullType {
    template<typename T>
    NullType& operator=(const T&)
    {
        static_assert(false, "Null type cannot be assigned");
        return *this;
    }
};

template<typename L, typename R>
struct TypeList {
    typedef L First;
    typedef R Rest;
};

#define TYPELIST1(A) TypeList<A, NullType>
#define TYPELIST2(A, B) TypeList<A, TypeList<B, NullType>>
#define TYPELIST3(A, B, C) TypeList<A, TypeList<B, TypeList<C, NullType>>>
#define TYPELIST4(A, B, C, D) \
TypeList<A, TypeList<B, TypeList<C, TypeList<D, NullType>>>>

template<typename T, typename U>
struct IsSame {
    static const bool value = false;
};

template<typename T>
struct IsSame<T, T> {
    static const bool value = true;
};

template<typename TL, typename F>
struct Contains {
    static const bool value = IsSame<typename TL::First, F>::value ||
                              Contains<typename TL::Rest, F>::value;
};

template<typename F>
struct Contains<NullType, F> {
    static const bool value = false;
};

template<typename TL, int R>
struct AtIndex;

template<typename F, typename R, int P>
struct AtIndex<TypeList<F,R>, P> {
    typedef typename AtIndex<R, P-1>::type type;
};

template<typename F, typename R>
struct AtIndex<TypeList<F, R>, 0> {
    typedef F type;
};

template<int P>
struct AtIndex<NullType, P> {
    typedef NullType type;
};

template<typename TL>
struct PrintIt {
    static void print() {
        std::cout << typeid(typename TL::First).name() << std::endl;
        PrintIt<typename TL::Rest>::print();
    }
};

template<>
struct PrintIt<NullType> {
    static void print() {
        std::cout << "NullType" << std::endl;
    }
};

#endif //TYPELIST_TYPELIST_H
