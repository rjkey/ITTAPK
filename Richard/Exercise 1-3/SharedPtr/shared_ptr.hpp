#pragma once
#include <cstdlib>

template <typename T> class shared_ptr {
	public:
        //Constructor
		shared_ptr(T* t) : _tPointer(t), _count(new int(1)){};
		
        //Copy constructor
        shared_ptr(const shared_ptr& other){
            _tPointer = other._tPointer;
            _count = other._count;
            *_count += 1;
        };

        //Destructor
        ~shared_ptr(){
            *_count = *_count - 1;
            if(*_count == 0){
                delete _tPointer;
                std::cout << "Everything is dead.." << std::endl;
            }
        };
        //Assignment operator overload
		shared_ptr& operator=(const shared_ptr& sp){
            sp.swap(*this);
        };

		T& operator*(){
            return *_tPointer;
        };
		
        T* operator->(){
            return _tPointer;
        };
		
        size_t count(){
            return *_count;
        };

    private:
        const T* _tPointer;
        int *_count;
        void swap(T& t){
            std::swap(this->_tPointer, t._tPointer);
            std::swap(this-> _count, t._count );
        }
};