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

## Exercise 2 - Partial specialization

### Exercise 2.1 Pointers
Since this is a partial specialization, one needs to define the specialization for the whole class. Apart from obviously
changing the destructor so that delete is called on all elements, the return types need to be updated so that where it
was previously T is now T* and where it was T* is now T**:
Our partial specialization does not provide a fill function. While it might make sense to set all elements to NULL, as-
signing all pointers to point to the same object would make the delete fail, since it would then call delete on the same
memory twice. If one wanted the fill with null functionality a fillWithNull() function could be implemented for the par-
tial specialization. Assigning all elements to null is also
done in our default constructor, so that one can know
whether or not dereferencing the elements is allowed.

### Exercise 2.2 Finding a specific element in our array of pointers
Obviously all the pointers and dereferences have to have one level added to them (T* becomes T** and *i becomes **i), but
aditionally the function now needs to check if the element is a null pointer, before trying to dereference and compare, to 
avoid segmentation faults.
A brief test is included in the end of the readme, also testing working as a test for 2.1

### Exercise 2.3 Reflection
This way of supporting allocated elements is not particularly elegant, since the whole class basically has to be written
again even though there's only a minimal change in the actual functionality. One advantage is the capability of not pro-
viding fill, since using it would be unsafe.
One method to improve the implementation would be to have a base class with the common functionality, and then writing
the base template and partial specializations as child classes to this class. This way only the destructor and fill would
have to be defined differently.
Another aproach to handling this would be to not provide the specialization, but require the user to use smart pointers
for the elements, in wich case the original implementation would work without fault. This would lead to much cleaner code,
but obviously requires the user to realize not to use raw pointers.
Lastly having the option to pass in a custom destructor in a similar fashion to the sharedPtr exercise could solve the
problem, with a medium of extra code.

## Exercise 3 - Accumulation

### 3.1 - Accumulation template functions

#### General considerations:
* In the given implementation our accumulation function is parameterized with the type U, which it expects to implement
  the typedef value_type. The value_type typedef is implemented in all std containers to allow templated utility func-
  tions to extract the type of the elements when parameterized by a container type. For example if one where to make the
  call "myAccumulation< MyArray<int, 20> >(myArray)" then the U::value_type would be an int.

* The line "typename U::value_type m = typename U::value_type();" creates a new U::value_type variable on the stack
  called m. In the given implementation this is the variable used to accumulate all the container objects by using the
  += operator

* The type held in value_type needs to correspond to the type pointertype returned by begin, end and operator[], and in
  this specific function we expect the type to work with operator+=

#### MyArray support and functionality verification:
In order to make this work with the MyArray class, the typedef is added to the class. The given myAccumulation implemen-
tation is added to the main.cpp file at the end, and used on both a MyArray and a std::vector object. This can all be
found in the main.cpp.
