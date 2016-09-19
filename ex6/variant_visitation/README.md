# Variant and Visitation

##Exercise 1 Defining and using `boost::variant`
The type Profanity has been declared, it generates
a random profanity from a pre determined list and writes
it to a string.

###Exercise 1.1 FELIX KIG PÅ Q HER

###Exercise 1.2 Fix the streamable issue
The stream operator has been overloaded to stream the profanity, so that's good.

## Exercise 2
###Visitation:
Visitation is a compile-time check of the bounded types of a given variant.
This check means that the programmer must explicitly handle each type in
the variant, or get a compile-time error if he fails to do so.
Visitation requires a visitation object that overloads the function call operator `operator()`.

###Functor
The functor writes a small message when a type is accesed stating the type
and the value of the variable.

###Compile-time error
I compiled my code with a part of the code in comments,
 ```c++
 class my_visitor : public boost::static_visitor<std::string>
 {
 public:
     std::string operator()(int & i) const
     {
         return std::string("the integer ") + std::to_string(i) + std::string(" has been accessed");
     }
 
     std::string operator()(Profanity & p) const
     {
         return std::string("the profanity ") + p.get_profanity() + std::string(" has been accessed");
     }
 
 //    std::string operator()(double & d) const
 //    {
 //        return std:: string("the double ") + std::to_string(d) + std::string(" has been accessed");
 //    }
 
 };
 ```
and surely enough, the compiler warns me that there is no match for a call to the
type which have not been implemented, which ensure that i do not make a mistake of 
forgetting something before compiling.

##Exercise 3 SNAK MED FELIX OM DET HER
