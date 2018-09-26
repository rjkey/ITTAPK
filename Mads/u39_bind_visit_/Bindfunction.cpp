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
#include <typeinfo>   //for using typeid

std::mutex stdioProt;

// protectiong cout, and defening events
void freeFunction( const std::shared_ptr<Event>& event )
{
   // Protecting stdio since its not thread safe
  std::lock_guard<std::mutex> lock(stdioProt );

  // using overload to print event
  // check for event type
  if (typeid(Event) == typeid(*event)) {
    std::cout << "Normal event detected in free function" << std::endl;
  }
  else if (typeid(EventOther) == typeid(*event)) {
    std::cout << "Event other detected in free function!" << std::endl;
  }
  else {
    std::cout << "Error Event in free function!!!" << std::endl;
  }
  // printer lige timestamp
  std::cout << *event;

  /*Opg 1.5
  the guard is there cause cout/stdio is not thread protected
  No need for releasing the mux, cause the shared_ptr takes care of it in the destruction???
  */
}


// Opg 2.1
// En functor er en overloaf af funktions operatoren()
// der så laves til at kalde alle med en hvis prototype/parametre
struct CB_functor
{
  void operator()(const std::shared_ptr<Event>& event) {
    // nothing
    std::cout << "CB functor called" << std::endl;
    std::cout << *event;
  }
} CB_functor_call;  // instans af struct'en


// opg 2.2 appends text to attach()
void withAnExtra(const std::shared_ptr<Event>& event, const std::string text)
{
   // Protecting stdio since its not thread safe
  std::lock_guard<std::mutex> lock(stdioProt );

  if (typeid(Event) == typeid(*event)) {
    std::cout << "Normal event detected + " << text << std::endl;
  }
  else if (typeid(EventOther) == typeid(*event)) {
    std::cout << "Event other detected + " << text << std::endl;
  }
  else {
    std::cout << "Error Event !!! + "  << text << std::endl;
  }
  // printer lige timestamp
  std::cout << *event;

}

// Wuuuut use?
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



    if (typeid(Event) == typeid(*event)) {
    std::cout << "Normal event detected in ReferenceObj" << std::endl;
    }
    else if (typeid(EventOther) == typeid(*event)) {
      std::cout << "Event other detected in ReferenceObj" << std::endl;
    }
    else {
      std::cout << "Error Event in ReferenceObj!!!" << std::endl;
    }
    // printer lige timestamp
    std::cout << *event;
    


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
  // Try to make several timers with different callbacks
  Timer t1( 4 );
  t1.attach( freeFunction );
  
  // opg 2.1
  t1.attach( CB_functor_call );

  // opg 2.2.1
  // bruger bind til at tilføje withAnExtra til attach
  // laver en placeholder på første argument af withAnExtra,
  // da det er det argument der er det sammen som i attach.
  t1.attach( std::bind(withAnExtra, std::placeholders::_1, "EXTRA TEXT") );

  // opg 2.2.2
  // opretter et object
  ReferenceObj RefObj;
  // da call (som ligger i klassen ReferenceObj) ikke er en fri funktion,
  // skal bind binde det til et specifikt objekt = RefObj
  // der anvendes referancer så der ikke laves kopier af objektet, men arbejdes på orginalen
  t1.attach( std::bind(&ReferenceObj::call, &RefObj, std::placeholders::_1) );








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
