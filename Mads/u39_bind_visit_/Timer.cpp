#include <iostream>
#include "Events.hpp"
#include "Timer.hpp"

// constructor med member-init
Timer::Timer( int timer) :
	eventTimer_( timer ), terminator_(false), counter_(0) {
	thread_ = new std::thread( std::bind( &Timer::timerThreadFunction, this ) );
}

Timer::~Timer() {
	terminator_ = true;
	thread_->join();
	delete thread_;
}

// implement attach
// attach skal tage et event, lave et Id til det, og gemme både event'et og ID'et i en map-container
int Timer::attach(std::function<void(const std::shared_ptr<Event> &)> cb) {
    callbacks_map[counter_] = cb;    //indsætter event/callback i map'et
    int id = counter_;            //opretter id til event'et
    counter_++;                   //klargør counter til næste event
    return id;
}


// implement detach
void Timer::detach(int cbid) {
  // erase the map-location with the specific callback id (cbid)
  callbacks_map.erase(cbid);
}

// gennemgår alle pladser i map'et
// og kalder alle callback funktioner der passer med 'second' argument.
// altså alle dem med samme event??
void Timer::notifyAll(const std::shared_ptr<Event> &any) {
  // std::cout << "Notify all called" << std::endl;   //debug
  for(auto CBs : callbacks_map) {
    CBs.second(any);
  }
  
  std::cout << std::endl;   // for pænt udprint
}



int Timer::timerThreadFunction() {
  int counter = 0;
  while( !terminator_ )
  {
    std::chrono::milliseconds sleepFor( 1000 );
    std::this_thread::sleep_for( sleepFor );

    notifyAll( std::make_shared<Event>() );
    if( ++counter >= eventTimer_ )
    {	
      counter = 0;
      std::cout << "EventOther created..." << std::endl;
      
      notifyAll( std::make_shared<EventOther>() );
    }
  }
  return 0;
}
