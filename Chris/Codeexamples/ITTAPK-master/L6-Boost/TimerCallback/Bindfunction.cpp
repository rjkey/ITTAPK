/*****************************************/
/* Copyright: DevelEdu 2013              */
/* Author: sha                           */
/*****************************************/

// bindanyfunction.cpp : Defines the entry point for the console application.
//

#include <string>
#include <iostream>
#include <mutex>
#include "Events.hpp"
#include "Timer.hpp"

#define EXIT_SUCCESS 0

std::mutex stdioProt;

void freeFunction(const std::shared_ptr<Event> &event) {
    // Protecting stdio since its not thread safe
    std::lock_guard<std::mutex> lock(stdioProt);

    if (typeid(Event) == typeid(*event)) {
        std::cout << "Normal event detected in free function" << std::endl;
    }
    else if (typeid(EventOther) == typeid(*event)) {
        std::cout << "Event other detected in free function!" << std::endl;
    }
}


void withAnExtra(const std::shared_ptr<Event> &event, const std::string text) {
    // Protecting stdio since its not thread safe
    std::lock_guard<std::mutex> lock(stdioProt);

    std::cout << "Message: " << text << std::endl;

}


class ReferenceObj {
public:
    ReferenceObj() : called_(0) {
    }

    void call(const std::shared_ptr<Event> &event) {
        // Protecting stdio since its not thread safe
        std::lock_guard<std::mutex> lock(stdioProt);

        std::cout << "Call amount: " << called_ << std::endl;

        ++called_;
    }

    int gotCalled() {
        return called_;
    }

private:
    int called_;
};

struct Funky {
    void operator()(const std::shared_ptr<Event> & event) {
        std::cout << *event;
    }
} funky;

int main() {
    // Try to make several timers with different callbacks
    ReferenceObj obj;

    Timer t1(4);
    t1.attach(&freeFunction);
    t1.attach(std::bind(&withAnExtra, std::placeholders::_1, "With something extra"));
    t1.attach(std::bind(&ReferenceObj::call, &obj, std::placeholders::_1));

    // The threads run naturally in the background (no clean up has been added for the threads)


    // You might wanna change the loop below such that you can extract the value of called_
    //  from your instance of ReferenceObj
    for (;;) {
        std::chrono::milliseconds sleepFor(1000);
        std::this_thread::sleep_for(sleepFor);
    }


    return EXIT_SUCCESS;
}
