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
happens. We use `boost::mpl` to hanlde multiple events as one.

### Ex 1.4 InstateInformation
In this part a machine level state variable indication the state of the
CD is used as a guard on the transition from RadioPlaying to CDPlaying
allowing the statemachine to stay in the RadioPlaying state, printing an
error msg, if a EvCD event occurs while no valid CD is in the machine.
This implies the use of two new Boost::statechart functionalities, name-
ly context which is used for statevariables from an outer context (in
this case the Radio context), and the discard_event() which is used as a
return value to indicate that no the event has been handled even though
no state transition occurs.

### Ex 1.5 History
In order to make the statemachine enter the same substate as it was in
when a state was left, the history functionality is used. This way a
state is passed its initial state in a shallow_history type, and
has_shallow_history is passed as an extra template param. No other
change is needed, and the radio remembers it's state when turned off and
on.
