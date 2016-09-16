#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <string>
#include <map>
#include <thread>
#include <functional>
#include <chrono>
#include <boost/any.hpp>

class Timer {
public:
    explicit Timer(int timer = 10);

    ~Timer();
    int attach(std::function<void (const std::shared_ptr<Event>&)> cb);
    void detach(int cbId);

private:
    void notifyAll(const std::shared_ptr<Event>& any);
    int timerThreadFunction();

private:
    int eventTimer_;
    std::thread *thread_;
    bool terminator_;
};


#endif
