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
   TestClass* myNormalPtr = new TestClass("FirstClass");
   SharedPtr<TestClass> *my1stPtr = new SharedPtr<TestClass>(myNormalPtr);
   SharedPtr<TestClass> my2ndPtr = myNormalPtr;
   this wont compile since the default constructor is declared explicit

### 2.2 Overloading
#### 2.2.1 Which overloads do we use?
The -> and * operator have been overloaded to accommodate our needs, and access the
right value when using our pointer. The equality operator might be a useful overload as well.

#### 2.2.3 Comparison Overloads


    if (*my1stPtr == *my3rdPtr)
    {
        std::cout << "true" << std::endl;
    }
    else if(*my1stPtr != *my3rdPtr) {
        std::cout << "false" << std::endl;
    }
this prints true if the resource (what the pointer points to) of the pointers is the same, and false if it isn't.

## 3 Destruction


## 4 Namespace
SharedPtr<> and associated free functions was placed in the namespace "felhak". The code works the
same whether it's placed in the namespace or not.