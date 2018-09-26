// Library which contains std::size_t
#include <cstddef>
#include <iostream>

// The implementation of a template is preferred to be in the header file to avoid defining types

template<typename T, typename D>
class SharedPtr
{
public:
	// Default constructor
	// Explicit makes sure that no implicit conversion is possible
	explicit SharedPtr(T * ptr, D d )
	{
		std::cout << "Default constructor" << std::endl;
		// Assign count_ with the value 1 of the type std::size_t
		count_ = new std::size_t(1);

		// address of pointer is saved in ptr_
		ptr_ = ptr;
	}

	// Explicitly defined copy constructor
	// The copy constructor is a constructor which creates an object by initializing it with an object of the same class, which has been created previously.
	// The copy constructor is used to:
	// .) Initialize one object from another of the same type.
	// .) Copy an object to pass it as an argument to a function.
	// .) Copy an object to return it from a function.
	SharedPtr(const SharedPtr& otherPtr)
	{
		std::cout << "Copy constructor" << std::endl;
		// count of otherPtr is saved in count_
		count_ = otherPtr.count_;
		// address of otherPtr is saved in ptr_
		ptr_ = otherPtr.ptr_;

		// The value of count_ is incremented
		++*count_;
	}

	// Assignment operator overload
	SharedPtr& operator=(const SharedPtr& otherPtr)
	{
		std::cout << "Assignment operator" << std::endl;
		// Check for self assignment
		if (this == &otherPtr)
			return *this; //self assignment

		// Remove old SharedPtr
		--*count_;

		// If last pointer then cleanup
		if(*count_ == 0)
		{
			delete ptr_;
			delete count_;
		}

		// Create new SharedPtr
		// count of otherPtr is saved in count_
		count_ = otherPtr.count_;
		// address of otherPtr is saved in ptr_
		ptr_ = otherPtr.ptr_;

		// The value of count_ is incremented
		++*count_;

		// Return address of new pointer (assigned pointer)
		return *this;
	}

	~SharedPtr()
	{
		// Decrement count_
		--*count_;

		// If last pointer then cleanup
		if (*count_ == 0)
		{
			delete ptr_;
			delete count_;
		}
	}

	T& operator*()
	{
		return *ptr_;
	}

	T* operator->()
	{
		return ptr_;
	}

	// size_t is a basic unsigned integer C/C++ type. It is the type of the result returned by sizeof operator.
	// The types size is chosen so that it could store the maximum size of a theoretically possible array of any type.
	// On a 32-bit system size_t will take 32 bits and on a 64-bit one - 64 bits.
	// Defined const to avoid change of *const_
	std::size_t count() const
	{
		return *count_;
	}

	//Exercise 2
	explicit operator bool() const
	{
		return ptr_ != nullptr;
	}
	
	bool operator==(const SharedPtr<T>& otherPtr) const
	{
		return ptr_ == otherPtr.ptr_;
	}

private:
	T* ptr_;
	// Reference counting. Keeps track of the number of references (the number of SharedPtr's).
	std::size_t* count_;
};

class Deleter 
{
	



}