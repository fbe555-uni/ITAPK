Basics concerning boost::signals2
=================================

##Exercise 1 Basic signaling
In order to test out the basic functionality, a signal called sensorSig is created according to the assignment
specifications:
'boost::signals2::signal<void(const std::string&, double)> sensorSig;'
once created, the signal object member function connect is used to hook up the three slots: freeSlot (implemented 
as a free function), slotFunctor (implemented as a struct overloading the () operator), and SlotRefObj(a class
implementing the desired functionality in it's member slotMe).
The three slots are registered to the signal as follows:
'''
sensorSig.connect(freeSlot);
sensorSig.connect(slotFunctor());
std::shared_ptr<SlotRefObj> sro = std::make_shared<SlotRefObj>();
sensorSig.connect(boost::bind(&SlotRefObj::slotMe, sro, _1, _2));
'''
Notice here how the function needs brackets (to create an instance), and the reference object is instantiated
whereafter the member is passed using boost::bind.

When the main function is run , a call to sensorSig() is made with the arguments SlotinessSensor and 114, and one
gets the following output
'''
im free...
SlotinessSensor: 114
I AM THE SLOTFUNCTOR!!!
SlotinessSensor: 114
you have been referenced
SlotinessSensor: 114
'''
demonstrating how all three slots are called.

