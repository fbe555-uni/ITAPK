ITAPK Exercise 1 - Array Template
=================================

## Exercise 1 - Implementing class MyArray Template

### 1.1 - The basic implementation
The implementation of MyArray can be found in the header file.
The template class is parameterized by the type T and the size_t s indicating the length of the array that is created.
The arguments for the assignment operator, copy constructor, fill and [] operator are const, since they are left un-
modified, as well as the functions begin, end and size, that need only read class members. The constness of the 
assignment operator and copy constructor is also required for the compiler to recognize them for what they are.
All the class functions are tested in main, by creating a MyArray instance, filling it, creating a new one from the
first, filling that with a new value, and then assigning the second to the first. This way all internal functions are 
hit. This code is found in main.cpp.

### 1.2 - Finding a specific element - take 1
The implementation of MyFind can be seen in MyArray.h. The implementation seen includes the changes from 1.3.
Finding the specified element is implemented by simply iterating through from begin to end, returning the iteration 
pointer if the item is found, and the end pointer otherwise.
The test snippit is run in the main.cpp

### 1.3 - Finding a specific element - take 2
As mentioned in the assignment, trying to use MyFind with a different type of literal than the MyArray parameter type, 
will not compile. This is because the first implementation is only parameterized by one type which will be deferred from
the arguments to the function. Runnung the previous snippet on an array of doubles, the compiler won't know wheather to 
convert to int or double. To make the function work for implicitly convertible types, all one needs to change is making 
the function be parameterized by two types, then the compiler will try and convert between the two. Now an error will 
only be thrown if the to types given the function have no implicit conversion. Had it not been an option to change the 
implementation one could have just called the function using the right type of literal, ie. 3.0 or 3f

### 1.4 - The copy constructor and assignment operator
In order to allow assignment from convertible types, a second template type is added to the to functions. The implemen-
tation is still just iterting over the array and copying each element, but now that there are two template types, the
compiler will do the necessary conversion if possible. In our implementation the copy and assignment operations do not
allow arrays of different length, since the length of the array is part of the type through the parameterization. Even
though it would be possible to create a new internal array, and return the right length through size, the MyArray object
would still be typed MyArray<T,s> with the original length.