#ifndef TEMPLATES_MYARRAY_H
#define TEMPLATES_MYARRAY_H

#include <cstdio>

template<typename T, size_t S>
class MyArray {
public:
    MyArray() {}

    ~MyArray() {}

    void fill(const T &value) {
        for (int i = 0; i < S; i++) {
            array[i] = value;
        }
    }

    template<typename O>
    MyArray(O &toCopy) {
        // Much copy construct
        // Very code
        // Such amaze
        O other = toCopy.begin();
        for (T iter = begin(); iter != end(); iter++, other++) {
            if (other != toCopy.end()) {
                *iter = *other;
            }
        }
    }

    T *begin() {
        return &array[0];
    }

    T *end() {
        return &array[S];
    }

    T &operator[](int i) {
        return array[i];
    }

    size_t size() const {
        return S;
    }

private:
    T array[S];
};

#endif //TEMPLATES_MYARRAY_H
