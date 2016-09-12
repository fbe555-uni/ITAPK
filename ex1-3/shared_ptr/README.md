ITAPK Hand-in 1 - Shared Pointer
================================

## 1 Making a basic smart pointer.
The shared pointer has been implemented using RAII and templates.
It implements the counted pointer idiom, in the way that it counts every 
pointer assigned to a certain resource, so we can track and handle deletion
when no pointers are assigned to the resource anymore. the assignment 
operator checks if it points to itself, and just returns itself (*this)
without counting the "new" pointer, since no new pointer is made.

## 2 Conversions
### 2.1 The 'explicit' constructor
The default constructor should be declared explicit, so that no assignment 
to regular references can be made, only to a shared pointer of our type, if we
try to assign to anything else, the compiler will give an error.
This is to make sure there is only one shared pointer, and not multiple groups.
e.g. if we have a shared pointer myShPtr to a resource that has s count of 2, and a 
shared pointer newShPtr to the same resource with a count of three, and the myShPtr
is destroyed, the resource will be destroyed as well, and then we have 3 counts of
newShPtr pointing to an invalid resource.

#### CODE SNIPPET FOR THE ABOVE    
```c++
TestClass* myNormalPtr = new TestClass("FirstClass");
SharedPtr<TestClass> *my1stPtr = new SharedPtr<TestClass>(myNormalPtr);
SharedPtr<TestClass> my2ndPtr = myNormalPtr;
this wont compile since the default constructor is declared explicit
```
### 2.2 Overloading
#### 2.2.1 Which overloads do we use?
The -> and * operator have been overloaded to accommodate our needs, and access the
right value when using our pointer. The equality operator might be a useful overload as well.

#### 2.2.3 Comparison Overload
The comparison overload is implemented so that i has the ability to compare pointers from a
base class with child classes. This is done through templates where the two arguments has the pos-
sibility of being a different class, thus allowing the comparsion of base-child class.
```c++
if (*my1stPtr == *my3rdPtr)
{
    std::cout << "true" << std::endl;
}
else if(*my1stPtr != *my3rdPtr) {
    std::cout << "false" << std::endl;
}
```
this prints true if the resource (what the pointer points to) of the pointers is the same, and false 
if it isn't.

## 3 Destruction
In order to allow custom destruction, the helper class ShPtrHelper and the child class ShPtrHelperImpl
are defined in the nested details namespace. This is the external polymorphisim approach, where the 
helper is used as a pseudo base class for all custom destructors, without the user having to actually 
inherit from any of our classes. Having the abstract ShPtrHelper allows for all the SharedPtr class in-
stances to have a member pointing to the helper object that is independent of the destructor functor 
type. If the custom-destructor constructor is invoked an instance of ShPtrHelperImpl that is typed 
according to the users destructor. 
When a shared pointer is created from another (copy construct or assignment), the ShPtrHelper pointer
_h is just assigned the value of _h in the original shared pointer, since this assures that all in-
stances will have the same custom destructor(or a nullptr if none).
When a SharedPtr is destroyed and the count becomes 0, then the _h object function operator overload 
is called if the pointer is not a nullptr. If the _h is a nullptr it means no custom destructor has
been provided, and delete is called as it normally would be.
Defining it in the details namespace shows the user that they need not use any of this, only to pass
some functor.

## 4 Namespace
SharedPtr<> and associated free functions was placed in the namespace "felhak". The code works the
same whether it's placed in the namespace or not, but providing your code in it's own namespace en-
sures that the user need not wory about naming conflicts, and makes it easy to see where the code
comes from.