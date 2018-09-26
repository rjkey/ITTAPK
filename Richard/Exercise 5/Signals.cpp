#include <string>
#include <iostream>
#include <boost/signals2.hpp>

void mySignal(const std::string& sensorName, double sensorValue){
    std::cout << sensorName << " " << sensorValue << std::endl;
}

class MyFunctor
{
    public:
    void operator()(){
        std::cout << "Hello from functor" << std::endl;
    }
};

int main(){
    MyFunctor functor;
    boost::signals2::signal<void ()> sig;
    sig.connect(functor);
    auto ms = std::bind(mySignal, "Hello", 3.3);
    sig.connect(ms);

    sig();
}