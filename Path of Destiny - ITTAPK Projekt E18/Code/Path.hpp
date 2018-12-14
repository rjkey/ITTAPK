#ifndef PATH_HPP
#define PATH_HPP

#include <string>
#include <iostream>

using namespace std; 



static string DirectionsStrings[] = {"continue ahead or turn left", "continue ahead or turn right", "turn left or right", "continue ahead or turn left or right"};


enum Directions
{
    LeftAhead,
    RightAhead,
    LeftRight, 
    LeftRightAhead
};


class Path
{
private:
    string areaName_; 
    string DirectionsToGo_;



public:
    Path(string name, uint directions);
    Path();
    ~Path();
    void setDirectionsToGo(uint directions);
    void show();

friend ostream& operator<< (ostream& os, const Path& path)
 {
     return os << "you have entered " << path.areaName_ << "you can "<< path.DirectionsToGo_ ; //<< std::endl;  
 }

};

Path::Path(string name, uint directions)
:areaName_(name)
{
    setDirectionsToGo(directions);
    
}

Path::Path()
{
    areaName_ = "unknown";
    DirectionsToGo_ = "Deadend";
}

Path::~Path()
{
}

void Path::setDirectionsToGo(uint directions)
{
    
    if (directions<4) {
        DirectionsToGo_ = DirectionsStrings[directions];
    }
    else
    {
        DirectionsToGo_ = "Deadend";
    }
    
    
}

void Path::show()
{
    cout<< "entered " << areaName_ << " you can "<<  DirectionsToGo_<< endl;

}


#endif // PATH_HPP