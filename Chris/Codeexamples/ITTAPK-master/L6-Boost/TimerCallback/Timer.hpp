#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <string>
#include <map>
#include <thread>
#include <functional>
#include <chrono>
#include <boost/any.hpp>
#include <vector>

class Timer {
public:
    explicit Timer(int timer = 10);

    ~Timer();

    int attach(std::function<void(const std::shared_ptr<Event> &)> cb);

    void detach(int cbId);

private:
    int timerThreadFunction();

    void notifyAll(const std::shared_ptr<Event> &any);

private:
    int eventTimer_;
    std::thread *thread_;
    bool terminator_;
    std::map<int, std::function<void (const std::shared_ptr<Event> &)>> callbacks_;
    int counter_;
};

#endif
