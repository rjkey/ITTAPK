#ifndef PATH_HPP
#define PATH_HPP

#include <string>
#include <iostream>
#include "Location.hpp"

using namespace std; 



static string DirectionsStrings[] = {"continue ahead or turn left", "continue ahead or turn right", "turn left or right", "continue ahead or turn left or right"};


enum Directions
{
    LeftAhead,
    RightAhead,
    LeftRight, 
    LeftRightAhead
};


class Path : virtual public Location
{
private:
    string AreaName_; 
    uint DirectionsToGo_;



public:
    Path(string name, uint directions);
    Path();
    ~Path();
    void setDirectionsToGo(uint directions);
    void show();


};

Path::Path(string name, uint directions)
:AreaName_(name)
{
    setDirectionsToGo(directions);
    
}

Path::Path()
{
    AreaName_ = "unknown";
    DirectionsToGo_ = NULL;
}

Path::~Path()
{
}

void Path::setDirectionsToGo(uint directions)
{
    
    if (directions<4) {
        DirectionsToGo_ = directions;
    }
    else
    {
        DirectionsToGo_ = NULL;
    }
    
    
}

void Path::show()
{
    cout<< "entered " << AreaName_ << " you can "<<  DirectionsStrings[DirectionsToGo_]<< endl;

}


#endif // PATH_HPP