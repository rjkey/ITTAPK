#ifndef GEAR_H
#define GEAR_H

#include "CosTypes.hpp"

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

  T getValue() const {
    return weapon_amour_;
  }

  void printGear(){
    std::cout << *this << std::endl;
  }

//////////////////// Overloads ////////////////////
/*/ Rule of 5: + Ostream
~Gear(){} // Destructor

Gear(const Gear& other) { // copy constructor     - Deep Copy??
  name_ = other.name_;
  weapon_amour_ = other.weapon_amour_;
}

Gear(Gear&& other) noexcept // move constructor
  : name_(std::exchange(other.name_, nullptr)),
    weapon_amour_(std::exchange(other.weapon_amour_, nullptr))
{}

Gear& operator=(const Gear& other) { // copy assignment - Shallow copy??
      return *this = Gear(other);
}

Gear& operator=(Gear&& other) noexcept { // move assignment
    std::swap(name_, other.name_);
    std::swap(weapon_amour_, other.weapon_amour_);
    return *this;
}//*/

//
  Gear(const Gear&) = default;              // Copy constructor
  Gear(Gear&&) = default;                   // Move constructor
  Gear& operator=(const Gear&) = default;   // Copy assignment operator
  Gear& operator=(Gear&&) = default;        // Move assignment operator
  virtual ~Gear() { }                       // Destructor//*/





//////////////////// Logic operations ////////////////////
  template<class Rhs, std::enable_if_t<!std::is_same<Rhs, Gear>{},int> =0 >
  friend bool operator==(Rhs const& ptr, Gear) {
    return !*ptr;
  }

  template<class Rhs, std::enable_if_t<!std::is_same<Rhs, Gear>{},int> =0 >
  friend bool operator!=(Rhs const& ptr, Gear) {
    return !(ptr==Gear{});
  }

  template<class Lhs, std::enable_if_t<!std::is_same<Lhs, Gear>{},int> =0 >
  friend bool operator==(Gear, Lhs const& ptr) {
    return !*ptr;
  }

  template<class Lhs, std::enable_if_t<!std::is_same<Lhs, Gear>{},int> =0 >
  friend bool operator!=(Gear, Lhs const& ptr) {
    return !(Gear{}==ptr);
  }

  friend bool operator==(Gear, Gear) {
    return true;
  }

  friend bool operator!=(Gear, Gear) {
    return false;
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

#endif // GEAR_H