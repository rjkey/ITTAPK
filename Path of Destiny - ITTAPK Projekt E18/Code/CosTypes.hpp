#ifndef COSTYPES_HPP
#define COSTYPES_HPP

#include <iostream>
#include <utility>  // for exchange(); -see overloads




//************** INTRO **************//
// Only subtract ATT from HP (=HP NOT the other way around!)
// Only subtract ATT from DEF (=DEF NOT the other way around!)
// DEF can be addet to HP (=HP all combinations)
// += and -= works on same types (all combinations)
// Comparing HP and ATT <, > (Only HP and ATT)
// Comparing HP and HP <, > (all combinations)
// Comparing ATT and ATT <, > (all combinations)
// Comparing DEF and DEF <, > (all combinations)
// Logic operations ==, != (all combinations)

// When working with HP, ATT and DEF
// Always add HP and DEF =HP, then subtract ATT also =HP
// When doing calculations between types, a temp type must be made SEE RULE 1 to 4!
// Ex:(H_tmp = HP1-ATT1) -> (HP1 = H_tmp)



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

//
// Struct for comparing validation (false)
template <class T, class = void>
struct HasValidateMethod : std::false_type {};

// struct for comparing validation (true)
template <class T>
struct HasValidateMethod<T, std::void_t<decltype(std::declval<T>().validate)> > : std::true_type {};

// What is valid, and what to return if not valied (one pr. type)
template<typename ST>
struct HP_Validation
{
  constexpr uint16_t validate(uint16_t value) const
  {
    if(value > 0) {
      return value;
    }
    else{
      return 0;
    }
  }  
};//*/

// the validation call
template<typename ST, typename T>
T&& validate(const ST& st, T&& t)
{
  if constexpr(HasValidateMethod<ST>::value)
                return st.validate(std::move(t));
  else
    return std::move(t);
}
//*/




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


  //////////////////// Logic operations ////////////////////
  template<class Rhs, std::enable_if_t<!std::is_same<Rhs, SafeType>{},int> =0 >
  friend bool operator==(Rhs const& ptr, SafeType) {
    return !*ptr;
  }

  template<class Rhs, std::enable_if_t<!std::is_same<Rhs, SafeType>{},int> =0 >
  friend bool operator!=(Rhs const& ptr, SafeType) {
    return !(ptr==SafeType{});
  }

  template<class Lhs, std::enable_if_t<!std::is_same<Lhs, SafeType>{},int> =0 >
  friend bool operator==(SafeType, Lhs const& ptr) {
    return !*ptr;
  }

  template<class Lhs, std::enable_if_t<!std::is_same<Lhs, SafeType>{},int> =0 >
  friend bool operator!=(SafeType, Lhs const& ptr) {
    return !(SafeType{}==ptr);
  }

  friend bool operator==(SafeType, SafeType) {
    return true;
  }

  friend bool operator!=(SafeType, SafeType) {
    return false;
  }//*/





  //////////////////// Overloads ////////////////////
  /*/ Rule of 5: + Ostream
  ~SafeType(){} // Destructor

  SafeType(const SafeType& other) { // copy constructor
    value_ = other.value_;
  }

  SafeType& operator=(const SafeType& other) { // copy assignment
        return *this = SafeType(other);
  }

  //SafeType(SafeType&& other) noexcept // move constructor
  //  : value_(std::exchange(other.value_, NULL))
  //{}

  SafeType(SafeType&& other) noexcept // move constructor
    : value_(std::move(other.value_))
  {}

  SafeType& operator=(SafeType&& other) noexcept { // move assignment
      //std::swap(value_, other.value_);
      return *this;
  }//*/

  //
  SafeType(const SafeType&) = default;              // Copy constructor
  SafeType(SafeType&&) = default;                   // Move constructor
  SafeType& operator=(const SafeType&) = default;   // Copy assignment operator
  SafeType& operator=(SafeType&&) = default;        // Move assignment operator
  virtual ~SafeType() { }                           // Destructor//*/

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
auto operator<(SafeType<T, Tag, Operations...> first, const SafeType<T, Tag, Operations...>& second)
{
    if( first.get() < second.get() ) {
      return true;
    }
    return false;
}

template<typename T, typename Tag, template<typename> typename... Operations>
auto operator>(SafeType<T, Tag, Operations...> first, const SafeType<T, Tag, Operations...>& second)
{
    if( first.get() > second.get() ) {
      return true;
    }
    return false;
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
using ATT = SafeType<int16_t, struct ATT_tag,  Addition, Subtraction, OutStream>;
using DEF = SafeType<int16_t, struct DEF_tag,  Addition, Subtraction, OutStream>;




/////////////////////////////////////////////
// ***** Define valid arithmetic ***** //
/////////////////////////////////////////////

// Only subtract ATT from HP (NOT the other way around!)
auto operator-(HP first, const ATT& second)
{
  first.set(first.get() - second.get());;
  return std::move(first);
}

// Only subtract ATT from DEF (NOT the other way around!)
auto operator-(DEF first, const ATT& second)
{
  first.set(first.get() - second.get());;
  return std::move(first);
}

// DEF can be addet to HP (all combinations)
auto operator+(HP first, const DEF& second)
{
  first.set(first.get() + second.get());;
  return std::move(first);
}
auto operator+(DEF first, const HP& second)
{
  first.set(first.get() + second.get());;
  return std::move(first);
}


// Comparing HP and ATT (all combinations)
auto operator<(HP first, const ATT& second)
{
  if( first.get() < second.get() ){
    return true;
  }
  return false;
}
auto operator<(ATT first, const HP& second)
{
  if( first.get() < second.get() ){
    return true;
  }
  return false;
}
auto operator>(HP first, const ATT& second)
{
  if( first.get() > second.get() ) {
    return true;
  }
  return false;
}
auto operator>(ATT first, const HP& second)
{
  if( first.get() > second.get() ) {
    return true;
  }
  return false;
}







#endif //COSTYPES_HPP

