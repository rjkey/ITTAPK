#ifndef MYVECTOR_H
#define MYVECTOR_H

#include "stddef.h"
#include <iostream>

template <typename T> class MyVector{
    public:
    explicit MyVector(int capacity = 10): _capacity(capacity), _size(0){
        try{
            _data = new T[_capacity];
        } catch(std::bad_alloc& ba){
            std::cerr << "Exception caught: " << ba.what() << std::endl;
        }
    }

    MyVector(const MyVector& other){
        _capacity = other._capacity;
        _size = other._size;

        try{
            _data = new T[_capacity];
        } catch(std::bad_alloc& ba){
            std::cerr << "Exception caught: " << ba.what() << std::endl;
        }

        for(int i = 0; i < _size; i++){
            try{
                _data[i] = other._data[i];
            } catch(...){
                std::cerr << "Exception caught: Assignment failed at i = " << i << std::endl; 
            }
        }
    }

    ~MyVector(){
        delete _data;
    }

    int size() const{
        return _size;
    }

    T& back(){
        return _data[_size-1];
    }

    void push_back(const T& t){
        
        if(_size == _capacity){
            _capacity = _capacity*2;
            T* tmp;
            try{
                tmp = new T[_capacity];
                std::copy(_data, _data+_size, tmp);
            } catch(std::bad_alloc& ba){
                std::cerr << "Exception caught: " << ba.what() << std::endl;
            } catch(...){
                std::cerr << "Exception caught: Copy failed in MyVector.h push_back" << std::endl;
            }          
            std::swap(tmp, _data);
        }
        
        try{
            _data[_size] = t;
        } catch(...){
           std::cerr << "Exception caught: Failed to assign data to array in push_back" << std::endl;  
        }
        _size++;
    }

    void pop_back(){
        T tmp = NULL;
        std::swap(_data[_size], tmp);
        _size--;
    }

    void insert(const T& t, size_t n){
        
        if(n < _capacity){
            try{
                _data[n] = t;
            } catch(...){
                std::cerr << "Exception caught: Failed to assign data to array in insert" << std::endl;  
            }
        }        
    }

    T* begin(){
        T* tmp = &_data[0];
        return tmp;
    }

    T* end(){
        T* tmp = &_data[_size+1];
        return tmp;
    };

    T& operator[](size_t i){
        return _data[i];
    };

    void PrintVector(){
        std::cout << "Capacity: " << _capacity << std::endl;
        for(int i = 0; i < _size; i++){
            std::cout << _data[i] << "\t";
        }
        std::cout << std::endl;
    }

    private:
    T* _data;
    int _capacity;
    int _size;
};

#endif