#ifndef TIMER_HPP_
#define TIMER_HPP_
#include <string>
#include <map>
#include <thread>
#include <functional>
#include <chrono>
#include <Events.hpp>
#include <typeinfo>   //for typeid

class Timer
{
public:
  explicit Timer( int timer = 10);
  ~Timer();

// attach tager en funktion som parameter, den funktion har et event som parameter kaldet cb
  int attach(std::function <void(const std::shared_ptr<Event>&)> cb); //cb = call back
// detach sletter pladsen i map'et der korrespondere med id'et
  void detach(int cbid);
  
private:
  int  timerThreadFunction();
  void notifyAll(const std::shared_ptr<Event> &any);
  
private:
  int eventTimer_;        // altal normal events 
  std::thread *thread_;   //??
  bool terminator_;       //??
  // map til at gemme ID(int) og events(object)
  std::map<int, std::function<void (const std::shared_ptr<Event> &)>> callbacks_map;
  // counter der inc/dec efter antal nye events, anvendes også som id
  int counter_;	
};



#endif
