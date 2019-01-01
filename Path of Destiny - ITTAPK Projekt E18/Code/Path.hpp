#ifndef PATH_HPP
#define PATH_HPP

#include <string>
#include <iostream>



static std::string DirectionsStrings[] = {"continue ahead or turn left", "continue ahead or turn right", "turn left or right", "continue ahead or turn left or right"};


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
    std::string areaName_; 
    std::string DirectionsToGo_;
    int directions__;


public:
    Path(std::string name, uint directions);
    Path();
    ~Path();
    void setDirectionsToGo(uint directions);
    std::string getDirectionsToGo();
    void show();
    int getValue();

friend std::ostream& operator<< (std::ostream& os, const Path& path)
 {
     return os << "you have entered " << path.areaName_ << " you can "<< path.DirectionsToGo_ ;
 }

};

Path::Path(std::string name, uint directions)
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

std::string Path::getDirectionsToGo()
{
    return DirectionsToGo_;
}


void Path::show()
{
    std::cout<< "you have entered " << areaName_ << " you can "<<  DirectionsToGo_<< std::endl;

}

int Path::getValue(){
    return directions__;
}

#endif // PATH_HPP