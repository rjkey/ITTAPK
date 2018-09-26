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

  
   if(typeid(Event)== typeid(*event))
   {
      std::cout << "Normal event detected "<< std::endl;  
      std::cout<< *event ;
   }
   else if (typeid(EventOther)== typeid(event)) 
   {
      std::cout<< "Other event detected" << std::endl;
      std::cout<< *event;
   }  
}


void withAnExtra(const std::shared_ptr<Event>& event, const std::string text)
{
   // Protecting stdio since its not thread safe
  std::lock_guard<std::mutex> lock(stdioProt );

  /* MISSING EVENT PRINT OUT */
   if(typeid(Event)== typeid(*event))
   {
      std::cout << "Normal event detected "<< text << std::endl;  
      std::cout<< *event ;
   }
   else if (typeid(EventOther)== typeid(event)) 
   {
      std::cout<< "Other event detected" << text << std::endl;
      std::cout<< *event;
   }  
}

struct Funktor {
    void operator()(const std::shared_ptr<Event> & event) {
        std::cout << " using functor: "<< std::endl << *event; 
    }
} funky;


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

    if(typeid(Event)== typeid(*event))
   {
      std::cout << "Normal event detected in refObj"<< std::endl;  
      std::cout<< *event ;
   }
   else if (typeid(EventOther)== typeid(event)) 
   {
      std::cout<< "Other event detected in refObj" << std::endl;
      std::cout<< *event;
   }  
    
    ++called_;
  }

   int gotCalled()
   {
      return called_;
   }
  
private:
   int   called_;
};



int main()
{
  ReferenceObj refObj;
  // Try to make several timers with different callbacks
  Timer t1( 4 );
  t1.attach( freeFunction );
  t1.attach( funky ); 
  t1.attach( std::bind(withAnExtra, std::placeholders::_1, "with some extra info"));
  t1.attach( std::bind(&ReferenceObj::call, &refObj, std::placeholders::_1));
  // The threads run naturally in the background (no clean up has been added for the threads)

   
  // You might wanna change the loop below such that you can extract the value of called_
  //  from your instance of ReferenceObj
  for(;;)
  {
    std::chrono::milliseconds sleepFor(1000);
    std::this_thread::sleep_for(sleepFor);
    //std::cout<< refObj.gotCalled()<< std::endl;
  }
   

  return EXIT_SUCCESS;
}
