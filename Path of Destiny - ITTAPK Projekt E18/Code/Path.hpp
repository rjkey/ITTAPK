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


class Path : public Location
{
private:
    string AreaName_; 
    uint DirectionsToGo_;



public:
    Path(string name, uint directions);
    ~Path();
    void show();


};

Path::Path(string name, uint directions)
{
    AreaName_ = name;
    DirectionsToGo_ = directions;
}

Path::~Path()
{
}

void Path::show()
{
    cout<< "entered " << AreaName_ << " you can "<<  DirectionsStrings[DirectionsToGo_]<< endl;

}
