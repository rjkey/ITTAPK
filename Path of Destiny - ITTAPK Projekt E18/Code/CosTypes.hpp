#ifndef COSTYPES_HPP
#define COSTYPES_HPP

#include <iostream>
#include <utility>  // for exchange(); -see overloads


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

  //////////////////// Overloads ////////////////////
// Rule of 5: + Ostream
~SafeType(){} // Destructor

SafeType(const SafeType& other) { // copy constructor
  value_ = other.value_;
}
/*
SafeType(SafeType&& other) noexcept // move constructor
  : value_(std::exchange(other.value_, NULL))
{}
*/
SafeType(SafeType&& other) noexcept // move constructor
  : value_(std::move(other.value_))
{}

SafeType& operator=(const SafeType& other) { // copy assignment
      return *this = SafeType(other);
}

SafeType& operator=(SafeType&& other) noexcept { // move assignment
    std::swap(value_, other.value_);
    return *this;
}//*/
//////////////////// Overloads end ////////////////////
  
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

// Only subtract ATT from HP (NOT the other way around!)
auto operator-(HP first, const ATT& second)
{
  first.set(first.get() - second.get());;
  return std::move(first);
}

// ???





//////////////////// TEMP class for Gear //////////////////////////////
template <typename T>
class Gear
{
public:
  // Default constructor
  Gear(){}

  // Constructor
  Gear (std::string name, T att_def){
      weapon_amour_ = att_def;
      name_ = name;
  }


  void printGear(){
    std::cout << *this << std::endl;
  }

//////////////////// Overloads ////////////////////
// Rule of 5: + Ostream
~Gear(){} // Destructor

Gear(const Gear& other) { // copy constructor
  name_ = other.name_;
  weapon_amour_ = other.weapon_amour_;
}

Gear(Gear&& other) noexcept // move constructor
  : name_(std::exchange(other.name_, nullptr)),
    weapon_amour_(std::exchange(other.weapon_amour_, nullptr))
{}

Gear& operator=(const Gear& other) { // copy assignment
      return *this = Gear(other);
}

Gear& operator=(Gear&& other) noexcept { // move assignment
    std::swap(name_, other.name_);
    std::swap(weapon_amour_, other.weapon_amour_);
    return *this;
}

/*/ Must be implemented for Hero.Show()
auto outstream() const { // Ostream operator
  return name_;
}//*/


friend std::ostream& operator<<(std::ostream& os, const Gear& G_Obj){ // Ostream overload
  return os << G_Obj.name_ << " (" << G_Obj.weapon_amour_ << ")";
}

private:
    std::string name_;
    T weapon_amour_;
};


/*/ Must be implemented for Hero.Show() (to print equipped items)
template<typename T>
std::ostream& operator<<(std::ostream& os, const Gear<T>& G_Obj)
{
  return os;
}//*/




#endif //COSTYPES_HPP

