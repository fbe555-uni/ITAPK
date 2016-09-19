# Boost::Function and Boost::Bind

## Exercise 1 Implementing the class `timer`

### 1.1/2
We've done this, and became very well acquainted with the code.

### 1.3/4/5 Implementing methods
To identify callback functions they are kept in a map, the map has a unique key
to be able to idnetify all callback functions for detaching them.
####`Attach()`:
Attach reads the callback into the map and assigns the function to a simple int ID (next_id).
every time a function is read into the map the value of next_id
is increased to ensure unique keys for all callback functions.

####`Detach()`:
Detach ensure deletion of every entry in the `callbacks_` map, it
uses the callback id which is generated and returned in/from attach.

####`notifyAll()`:
`notifyAll()` iterates through all callback functions in the
`callbacks_`  map, and calls every function with the event parameter `any`. 

#### Missing part of `freeFunction()`:
A printout was added that checks what kind of event it recieves.
It utilises typeid casting on the received event and compares with the typeid of 
the two classes `Event` and `EventOther`

## Exercise 2 Using other callback entities:

### 2.1 Functor
In order to use a functor for the callback, all that has to be done is implementing a struct overloading the 
() operator. The implemented function is the same as the freeFunction, only printing out functor rather than 
freeFunction.

### 2.2 Using boost::bind()

#### 2.2.1 withExtra
In order to use the free function withExtra, which takes a string as well as an event pointer, a callable object
taking only one input parameter needs to be created. To do this one can use the boost::bind function passing both
the function pointer, a placeholder indicating that the first argument should be forwarded, and a value to give 
as the second parameter. 't1.attach(boost::bind(withAnExtra, _1, "extra tick-tock"));'

#### 2.2.2 member function
another usecase for boost::bind is when a member function needs to be passed. Obviously the function then needs a 
referance to the instance on which the function should be called, as well as the address of the function to call.
Note here that one has to use the adress operator on the function name in this case: 
't1.attach(boost::bind(&ReferenceObj::call, r1, _1));'
were r1 is an instantiation of ReferenceObj.

