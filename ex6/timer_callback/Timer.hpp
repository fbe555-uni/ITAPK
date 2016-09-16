#ifndef TIMER_HPP_
#define TIMER_HPP_
#include <string>
#include <map>
#include <thread>
#include <functional>
#include <chrono>
#include <boost/any.hpp>

class Timer
{
public:
  explicit Timer( int timer = 10);
  
  ~Timer();  
  
private:
  int  timerThreadFunction();
  
private:
  int           eventTimer_;
  std::thread*	thread_;
  bool          terminator_;	
};






#endif
