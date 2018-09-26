/*****************************************/
/* Copyright: DevelEdu 2013              */
/* Author: sha                           */
/*****************************************/

// bindanyfunction.cpp : Defines the entry point for the console application.
//

#include <string>
#include <iostream>
#include <mutex>
#include <functional>
#include "Events.hpp"
#include "Timer.hpp"

std::mutex stdioProt;


void freeFunction( const std::shared_ptr<Event>& event )
{
   // Protecting stdio since its not thread safe
  std::lock_guard<std::mutex> lock(stdioProt );

    if(typeid(*event) != typeid(Event)){
      
      std::cout << "A very special event is detected!" << std::endl;
    } 
    else{
      std::cout << "This is the standard event..." << std::endl;
    }
}

void withAnExtra(const std::shared_ptr<Event>& event, const std::string text)
{
   // Protecting stdio since its not thread safe
  std::lock_guard<std::mutex> lock(stdioProt );

  std::cout << text << std::endl;

}


class ReferenceObj
{
public:
   ReferenceObj() : called_(0) 
   {
   }

  void call( const std::shared_ptr<Event>& event )
  {
    // Protecting stdio since its not thread safe
    std::lock_guard<std::mutex> lock(stdioProt );
    std::cout << "Call in Reference obj" << std::endl;
    /* MISSING EVENT PRINT OUT */
    
    ++called_;
  }

   int gotCalled()
   {
      return called_;
   }
  
private:
   int   called_;
};

class MyFunctor
{
    public:
    void operator()(const std::shared_ptr<Event> & event){
        std::cout << "My functor just got used as callback!!" << std::endl;
    }
};

int main()
{
  MyFunctor func;
  ReferenceObj refObj;
  // Try to make several timers with different callbacks
  Timer t1( 4 );
  t1.attach(freeFunction);
  t1.attach(func); //using MyFunctor as callback function
  t1.attach(std::bind(&withAnExtra, std::placeholders::_1, "Placeholder"));
  t1.attach(std::bind(&ReferenceObj::call, refObj, std::placeholders::_1));

  // The threads run naturally in the background (no clean up has been added for the threads)

   
  // You might wanna change the loop below such that you can extract the value of called_
  //  from your instance of ReferenceObj
  for(;;)
  {
    std::chrono::milliseconds sleepFor(1000);
    std::this_thread::sleep_for(sleepFor);
  }
   

  return EXIT_SUCCESS;
}
