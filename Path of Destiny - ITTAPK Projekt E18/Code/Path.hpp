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
    int directions__;



public:
    Path(string name, uint directions);
    Path();
    ~Path();
    void setDirectionsToGo(uint directions);
    string getDirectionsToGo();
    void show();
    int getValue();

friend ostream& operator<< (ostream& os, const Path& path)
 {
     return os << " you have entered " << path.areaName_ << " you can "<< path.DirectionsToGo_ ; //<< std::endl;  
 }

};

Path::Path(string name, uint directions)
:areaName_(name), directions__(directions)
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

string Path::getDirectionsToGo()
{
    return DirectionsToGo_;
}


void Path::show()
{
    cout<< "entered " << areaName_ << " you can "<<  DirectionsToGo_<< endl;

}

int Path::getValue(){
    return directions__;
}

#endif // PATH_HPP