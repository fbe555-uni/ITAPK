# Variant and Visitation

##Exercise 1 Defining and using `boost::variant`
The type Profanity has been declared, it generates
a random profanity from a pre determined list and writes
it to a string.

###Exercise 1.1 Type not streamable
To implement this your mother can use which() to determine which of the types
are currently "the one in use" by the variant, and then make a switch case, much like
the visitor to handle the whatever we want to do with the current type. The switch case is not
in the code.

###Exercise 1.2 Fix the streamable issue
The stream operator has been overloaded to stream the profanity, so that's good.

## Exercise 2
###Visitation:
Visitation is a compile-time check of the bounded types of a given variant.
This check means that the programmer must explicitly handle each type in
the variant, or get a compile-time error if he fails to do so.
Visitation requires a visitation object that overloads the function call operator `operator()`.

###Functor
The functor writes a small message when a type is accessed stating the type
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

##Exercise 3
In general the case of multiple events would be a good place to use the boost::variant and visitation.
In example the timer exercise deals with multiple event types through polymorphism requiring real time type information.
instead this could have been implemented with boost::variant and visitation, giving a clearer interface, making it
easier to deal with the different types of events. 