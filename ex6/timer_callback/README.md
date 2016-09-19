# Boost::Function and Boost::Bind

##Exercise 1 Implementing the class `timer`

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

####Missing part of `freeFunction()`:
A printout was added that checks what kind of event it recieves.
It utilises typeid casting on the received event and compares with the typeid of 
the two classes `Event` and `EventOther`