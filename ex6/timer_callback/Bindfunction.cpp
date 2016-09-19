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

void freeFunction(const std::shared_ptr<Event> &event) {
    // Protecting stdio since its not thread safe
    std::lock_guard<std::mutex> lock(stdioProt);
    std::cout << "freeFunction received the following "
    if(typeid(*event) == typeid(Event)) {
        std::cout << "Event: ";
    }else if(typeid(*event) == typeid(EventOther)){
        std::cout << "EventOther: ";
    }else{
        std::cout << "Unknown Event derivation: ";
    }
    std::cout << *event << std::endl;
}


void withAnExtra(const std::shared_ptr<Event> &event, const std::string text) {
    // Protecting stdio since its not thread safe
    std::lock_guard<std::mutex> lock(stdioProt);

    std::cout << "withAnExtra called. forwarding to freeFunction:" << std::endl;
    freeFunction(event);
    std::cout << "With the following extra: " << text << std::endl;

}

struct testFunctor{
    void operator()(const std::shared_ptr<Event> &event){
        std::cout << "Functor called. forwarding to freeFunction:" << std::endl;
        freeFunction(event);
    }
};


class ReferenceObj {
public:
    ReferenceObj() : called_(0) {
    }

    void call(const std::shared_ptr<Event> &event) {
        // Protecting stdio since its not thread safe
        std::lock_guard<std::mutex> lock(stdioProt);

        std::cout << "ReferenceObj called. forwarding to freeFunction:" << std::endl;
        freeFunction(event);
        std::cout << "This is the " << ++called_ << "time this obj has been called" << std::endl;
    }

    int gotCalled() {
        return called_;
    }

private:
    int called_;
};


int main() {
    // Try to make several timers with different callbacks
    Timer t1(4);
    t1.attach(freeFunction);
    testFunctor tf;
    t1.attach(tf);
    t1.attach(boost::bind())


    // The threads run naturally in the background (no clean up has been added for the threads)


    // You might wanna change the loop below such that you can extract the value of called_
    //  from your instance of ReferenceObj
    for (;;) {
        std::chrono::milliseconds sleepFor(1000);
        std::this_thread::sleep_for(sleepFor);

    }


    return EXIT_SUCCESS;
}
