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

    //if(dynamic_cast<EventOther*>(&(*event)) != 0){
    //ss << typeid(*event).name();
    if(typeid(*event) == typeid(EventOther)){
        ss << "EventOther: ";
    }else if(typeid(*event) == typeid(Event)){
        ss << "Event: ";
    }else{
        ss << "Unknown derivative: ";
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

    // Try to make several timers with different callbacks
    Timer t1(4);
    std::cout << "Adding a freeFunction callback, a functor callback and a withExtra freefunction callback using boost::bind" << std::endl;
    int free = t1.attach(freeFunction);
    testFunctor tf;
    int functor = t1.attach(tf);
    t1.attach(boost::bind(withAnExtra, _1, "extra tick-tock"));
    std::cout << "callbacks added. waiting for 3 seconds." << std::endl;
    std::chrono::milliseconds sleepFor(3000);
    std::this_thread::sleep_for(sleepFor);

    std::cout << "Removing the freeFunction and functor callbacks to test detach" << std::endl;
    t1.detach(free);
    t1.detach(functor);
    std::cout << "Adding two reference object callback." << std::endl;
    std::shared_ptr<ReferenceObj> r1 = std::make_shared<ReferenceObj>();
    std::shared_ptr<ReferenceObj> r2 = std::make_shared<ReferenceObj>();
    t1.attach(boost::bind(&ReferenceObj::call, r1, _1));
    t1.attach(boost::bind(&ReferenceObj::call, r2, _1));
    std::cout << "ReferenceObj callbacks added. will now start printing the objects gotCalled() value." << std::endl;

    for (;;) {
        std::chrono::milliseconds sleepFor(1000);
        std::this_thread::sleep_for(sleepFor);
        std::cout << "r1 called " << r1->gotCalled() << " times." << std::endl;
        std::cout << "r2 called " << r2->gotCalled() << " times." << std::endl;


    }

    return EXIT_SUCCESS;
}
