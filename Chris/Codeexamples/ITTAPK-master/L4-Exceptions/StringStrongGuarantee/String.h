//
// Created by dennis on 12/09/16.
//

#ifndef EXCEPTIONS_STRING_H
#define EXCEPTIONS_STRING_H

#include <cstring>
#include <ostream>
#include <vector>
#include <iostream>

namespace my {
    class String {
    public:
        String() {}

        String(const char *s) : s_(s, s + strlen(s)) {}

        String(const String &other) : s_(other.s_) {}

        String &operator=(const String &other) {
            String tmp(other);
            std::swap(tmp.s_, this->s_);
            return *this;
        }

        ~String() {}

        friend std::ostream &operator<<(std::ostream &os, const String &string);

    private:
        std::vector<char> s_;
    };

    std::ostream &operator<<(std::ostream &os, const my::String &string) {
        for (auto ptr : string.s_) {
            os << ptr;
        }
        return os;
    }
}


#endif //EXCEPTIONS_STRING_H
