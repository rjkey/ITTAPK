#ifndef LOCATION_HPP 
#define LOCATION_HPP
#include <string>

using namespace std;

class Location
{
private:
    
public:
    Location();
    ~Location();
    virtual void show() const;
};

Location::Location()
{

}

Location::~Location()
{
}

void Location::show() const
{

}

#endif // LOCATION_HPP