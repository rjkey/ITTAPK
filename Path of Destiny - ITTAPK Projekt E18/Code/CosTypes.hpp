#ifndef COSTYPES_HPP
#define COSTYPES_HPP

#include <iostream>


/////////////////////////////////////////////
// ***** x= Operator Definition ***** //
/////////////////////////////////////////////

// takes a SafeType
template<typename ST>
struct Multiply 
{
  ST& operator *= (const ST& other)
  {
    // casts the input type (other) to whatever *this type is
    // and use the set() function to store the result of Mul-operation in it self.
    static_cast<ST&>(*this).set(static_cast<ST&>(*this).get() * other.get());    
    return static_cast<ST&>(*this);    
  }
  
};

template<typename ST>
struct Addition 
{
  ST& operator += (const ST& other)
  {
    static_cast<ST&>(*this).set(static_cast<ST&>(*this).get() + other.get());    
    return static_cast<ST&>(*this);
  }
  
};

template<typename ST>
struct Subtraction 
{
  ST& operator -= (const ST& other)
  {
    static_cast<ST&>(*this).set(static_cast<ST&>(*this).get() - other.get());    
    return static_cast<ST&>(*this);
  }
  
};


template<typename ST>
struct OutStream 
{
  auto outstream() const
  {
    return static_cast<const ST&>(*this).get();
  }
  
};



/////////////////////////////////////////////
// ***** SafeType Validation ***** //
/////////////////////////////////////////////

// Struct for comparing validation (false)
template <class T, class = void>
struct HasValidateMethod : std::false_type {};

// struct for comparing validation (true)
template <class T>
struct HasValidateMethod<T, std::void_t<decltype(std::declval<T>().validate)> > : std::true_type {
};

// What is valid, and what to return if not valied (one pr. type)
template<typename ST>
struct HP_Validation
{
  constexpr uint16_t validate(uint16_t value) const
  {
    if(value < 0)
      return 0;
    return value;
  }  
};

// the validation call
template<typename ST, typename T>
T&& validate(const ST& st, T&& t)
{
  if constexpr(HasValidateMethod<ST>::value)
                return st.validate(std::move(t));
  else
    return std::move(t);
}





/////////////////////////////////////////////
// ***** SafeType Class ***** //
/////////////////////////////////////////////
// takes a type, a tag, and a list of what is valid (add, mul, ect..)
template<typename T, typename Tag, template<typename> typename... Operations>
class SafeType : public Operations<SafeType<T, Tag, Operations...>>...
{
public:
  using Type = T;   // why??
  // Default constructor (cant use setFunctions in Hero otherwise!)
  SafeType()
  { }
  
  // SafeType takes the chosen default type and stores it in value_ after validation
  SafeType(T value) : value_(validate(*this, std::move(value)))
  { }

  // Get function
  constexpr T get() const 
  {
    return value_;
  }
  // Set function
  constexpr void set(T&& value) 
  {
    value_ = validate(*this, std::move(value));
  }
  
private:
  T value_;
};






/////////////////////////////////////////////
// ***** Operator Definition ***** //
/////////////////////////////////////////////
template<typename T, typename Tag, template<typename> typename... Operations>
auto operator*(SafeType<T, Tag, Operations...> first, const SafeType<T, Tag, Operations...>& second)
{
    first *= second;
  return std::move(first);
}

template<typename T, typename Tag, template<typename> typename... Operations>
auto operator+(SafeType<T, Tag, Operations...> first, const SafeType<T, Tag, Operations...>& second)
{  
    first += second;
  return std::move(first);
}

template<typename T, typename Tag, template<typename> typename... Operations>
auto operator-(SafeType<T, Tag, Operations...> first, const SafeType<T, Tag, Operations...>& second)
{
    first -= second;
  return std::move(first);
}

template<typename T, typename Tag, template<typename> typename... Operations>
std::ostream& operator<<(std::ostream& os, const SafeType<T, Tag, Operations...>& first)
{
  os << first.outstream();
  return os;
}

template<typename T, typename Tag, template<typename> typename... Operations>
std::istream& operator>>(std::istream& is, SafeType<T, Tag, Operations...>& first)
{
  T t{};
  
  is >> t;
  first.set(std::move(t));
  return is;
}





/////////////////////////////////////////////
// ***** Define Costume Types ***** //
/////////////////////////////////////////////
using HP = SafeType<int16_t, struct HP_tag,     Addition, Subtraction, OutStream>;
using ATT = SafeType<uint16_t, struct ATT_tag,  Addition, Subtraction, Multiply, OutStream>;
using DEF = SafeType<uint16_t, struct DEF_tag,  Addition, Subtraction, Multiply, OutStream>;




/////////////////////////////////////////////
// ***** Define valid arithmetic ***** //
/////////////////////////////////////////////
auto operator-(HP first, const ATT& second)
{
  first.set(first.get() - second.get());;
  return std::move(first);
}









//


template <typename T>
class Gear
{
public:
    Gear(){}

    Gear (std::string name, T att_def){
        weapon_amour = att_def;
        name_ = name;
    }
    void printGear(){
      std::cout << name_ << "\t" << weapon_amour << std::endl;
    }

  
  /*auto outstream() const
  {
    return name_;
  }*/


private:
    std::string name_;
    T weapon_amour;
};


/*template<typename T>
std::ostream& operator<<(std::ostream& os, const Gear<T>& first)
{
  os << first.outstream();
  return os;
}*/

//*/



#endif //COSTYPES_HPP
