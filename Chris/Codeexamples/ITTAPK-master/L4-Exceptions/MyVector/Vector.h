//
// Created by dennis on 12/09/16.
//

#ifndef MYVECTOR_VECTOR_H
#define MYVECTOR_VECTOR_H

#include <exception>
#include <string.h>

namespace my {
    template<typename T>
    class Vector {
    public:
        explicit Vector(int capacity = 10) : capacity_(capacity), latest_(0), data_(new T[capacity]) {}

        Vector(const Vector &other) {
            if (this == &other) return;

            capacity_ = other.capacity_;
            latest_ = other.latest_;
            data_ = new T[capacity_];

            std::copy(other.data_, other.data_ + other.capacity_, data_);
        }

        Vector &operator=(const Vector &other) {
            std::cout << "assignment!!" << std::endl;
            Vector tmp(other);
            swap(tmp);
            return *this;
        }

        ~Vector() {
            delete[] data_;
        }

        int size() const {
            return capacity_;
        }

        T &back() {
            return *data_;
        }

        void push_back(const T &t) {
            if (latest_ < capacity_) {
                data_[latest_] = t;
                latest_++;
            }
        }

        void pop_back() {
            latest_--;
        }

        void insert(const T &t, int n) {}

        void swap(Vector &other) {
            std::swap(data_, other.data_);
        }

        T *begin() {
            return data_;
        }

        T *end() {
            return data_ + latest_;
        }

        T &operator[](int i) {
            return data_[i];
        }

    private:
        int capacity_;
        int latest_;
        T *data_; // Contains the actual elements - data on the heap
    };
}

#endif //MYVECTOR_VECTOR_H
