#ifndef TIMER_HPP_
#define TIMER_HPP_
#include <string>
#include <map>
#include <thread>
#include <functional>
#include <chrono>

class Timer
{
public:
  explicit Timer( int timer = 10);
  int attach(std::function<void (const std::shared_ptr<Event>&)> cb);
  void detach(int cbId);
  ~Timer();  
  
private:
  int  timerThreadFunction();
  void notifyAll(const std::shared_ptr<Event>& any);
  
  
private:
  int           eventTimer_;
  std::thread*	thread_;
  bool          terminator_;
  std::map<int, std::function<void (const std::shared_ptr<Event> &)>> callbacks_;
  std::function<void (const std::shared_ptr<Event> &)> test_;
  int counter_;
};






#endif
