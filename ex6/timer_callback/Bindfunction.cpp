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
#include <sstream>
#include "Events.hpp"
#include "Timer.hpp"
#include "boost/bind.hpp"
#include <typeinfo>
#include "Events.hpp"

std::mutex stdioProt;

std::string event2String(const std::shared_ptr<Event>& event){
    std::stringstream ss;

    if(typeid(*event) == typeid(Event)) {
        ss << "Event: ";
    }else if(typeid(*event) == typeid(EventOther)){
        ss << "EventOther: ";
    }else{
        ss << "Unknown Event derivation: ";
    }
    ss << *event;
    return ss.str();
}

void freeFunction(const std::shared_ptr<Event> &event) {
    // Protecting stdio since its not thread safe
    std::lock_guard<std::mutex> lock(stdioProt);
    std::cout << "freeFunction received the following " << event2String(event);
}


void withAnExtra(const std::shared_ptr<Event> &event, const std::string text) {
    // Protecting stdio since its not thread safe
    std::lock_guard<std::mutex> lock(stdioProt);

    std::cout << "withAnExtra received the following: " << event2String(event);
    std::cout << "With the following extra: " << text << std::endl;

}

struct testFunctor{
    void operator()(const std::shared_ptr<Event> &event){
        std::cout << "Functor received the following: " << event2String(event);
    }
};


class ReferenceObj {
public:
    ReferenceObj() : called_(0) {
    }

    void call(const std::shared_ptr<Event> &event) {
        // Protecting stdio since its not thread safe
        std::lock_guard<std::mutex> lock(stdioProt);

        std::cout << "ReferenceObj received the following: " << event2String(event);
        std::cout << "This obj has been called " << ++called_ << " times." << std::endl;
    }

    int gotCalled() {
        return called_;
    }

private:
    int called_;
};


int main() {
    Event e;
    EventOther eo;
    Event* e_ptr = new Event();
    Event* eo_ptr = new EventOther();
    std::shared_ptr<Event> eo_shptr = std::make_shared<EventOther>();

    std::cout << "e: " << typeid(e).name() << std::endl;
    std::cout << "eo: " << typeid(eo).name() << std::endl;
    std::cout << "*e_ptr: " << typeid(*e_ptr).name() << std::endl;
    std::cout << "*eo_ptr: " << typeid(*eo_ptr).name() << std::endl;
    std::cout << "*eo_shptr: " << typeid(*eo_shptr).name() << std::endl;


    // Try to make several timers with different callbacks
    Timer t1(4);
    std::cout << "Adding a freeFunction callback, a functor callback and a withExtra freefunction callback using boost::bind" << std::endl;
    int free = t1.attach(freeFunction);
    testFunctor tf;
    int functor = t1.attach(tf);
    t1.attach(boost::bind(withAnExtra, _1, "extra tick-tock"));
    std::cout << "callbacks added. waiting for 3 seconds." << std::endl;
    std::chrono::milliseconds sleepFor(5000);
    std::this_thread::sleep_for(sleepFor);

    std::cout << "Removing the freeFunction and functor callbacks to test detach" << std::endl;
    t1.detach(free);
    t1.detach(functor);
    std::cout << "Adding two reference object callback." << std::endl;
    ReferenceObj r1, r2;
    r1.call(std::make_shared<Event>());
    t1.attach(boost::bind(&ReferenceObj::call, r1, _1));
    t1.attach(boost::bind(&ReferenceObj::call, r2, _1));
    std::cout << "ReferenceObj callbacks added. will now start printing the objects gotCalled() value." << std::endl;

    for (;;) {
        std::chrono::milliseconds sleepFor(1000);
        std::this_thread::sleep_for(sleepFor);
        std::cout << "r1 called " << r1.gotCalled() << " times." << std::endl;
        std::cout << "r2 called " << r2.gotCalled() << " times." << std::endl;


    }

    return EXIT_SUCCESS;
}
