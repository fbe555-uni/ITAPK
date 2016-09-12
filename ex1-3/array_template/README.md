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

It is evident from inspecting the code for the primary template MyArray that if an instantiation
is parameterized by a pointer element e.g. std::string* , thus an allocated resource, then these
will not be deallocated upon MyArray ’s destruction.
Therefore create a partial specialization that caters for pointers and add a destructor that
traverse the array and deletes each and every element using delete .
Things to consider in this endeavor:
• The return type for functions begin() and end()
• The return type for function operator[](int) especially, remember code like this must
work: my[2] = new std::string , assuming it handles std::string* elements!
• What do you propose to do with the function fill() (that is implement - then how or
drop it) ? - Explanation required!
Exercise 2.2 Finding a specific element in our array of pointers
Again we want to be able ti find a specific element in our array. In that respect we could use the
template function myfind() which we created earlier, however it would not work as expected,
but rather just compare pointers. We therefore need to create an overload of this template
function to work with our new partial class template.
The desired signature for this template function is:
Listing 2.1: Using template function myfind() for our new partial class template
template < typename T, typename V>
T** myfind (T** first , T** last , const V& v)
1
2
A simple usage scenario could be:
3Templates
Søren Hansen <sha@ase.au.dk>
V1.2
Listing 2.2: Using template function myfind() for our new partial class template
my [5] = new std :: string ("Hello "); // Assuming that my is a MyArray of
string pointers
1
2
3
std :: cout << " Looking for 'Hello '? " << ( myfind (my.begin (), my.end (),
std :: string (" Hello ")) != my.end ()? " found " : "sry no") << std :: endl;
Exercise 2.3 Reflection
In this particular design it was chosen that a partial specialization would be the choice to handle
the deallocation scheme.
If you had had the choice designwise, would you have done the same?
Whether yes or no, discuss pros and cons regarding this solution or this solution as opposed to
your preferred solution.
Simply stating one point about another design is not an answer.

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