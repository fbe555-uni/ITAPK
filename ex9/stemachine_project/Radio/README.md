Exercise 9 - Boost::Statechart
==============================

## Exercise 1 - the vision

### Ex 1.1 - SimpleStates
In the SimpleStates folder, an implementation containing only two states
and two events corresponding to transistions in wither direction.
This code shows the basic mechanics of the library the clearest. 
All the baseclass templates use curiously recurring template pattern, 
allowing behaviour analogous to virtual functions, but without the cost
of dynamic polymorphism. In the static polymorphism scheme, the poly-
morphism is resolved at compiletime, allowing for more efficient code.

### Ex 1.2 - MultipleHierarchicalStates
in the MultipleHierarchicalStates folder, an implementation with nested 
states is presented. What is most noteworthy here is the state templati-
zation from 3 parameters: the derived class, the context, and the init-
ial state. Having multiple levels of states, the context is not nesces-
sarily the statemachine, but could be another state. If the state you're
defining has substates, the third parameter is used to define the inital
substate.

### Ex 1.3 GuardedTransInCustomReact
In this exercise we added a check to see if the state   we're trying to 
enter is valid. We do this by adding a bool to the EvCDState that deter-
mines whether or not the input CD is valid, if it is valid, we change 
to CD Playing. If it is not valid, the state is returned to Radio Playing.
The interesting stuff happens in `CDLoading`, where the validity check 
happens. We use `boost::mpl` to handle multiple events at once.
