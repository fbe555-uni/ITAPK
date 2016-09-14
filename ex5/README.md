#STL Algorithms

##Exercise 1 Basic STL

###Exercise 1.1 istream_operator/ostream_operator

####Exercise 1.1.1 Updating file reading
To update the readProductDB function to use std::copy, one needs 3 things: an itterator marking the 
beginning of the source, one marking the end of the source, and one marking the target.
The input begin itterator is obtained by creating an istream_itterator<Product> from the file object.
The input end itterator is obtained from the default constructor since this works for EOF. 
Since we want to add the elements to our container using push_back like behaviour, the target it-
terator is created using back_inserter. 
The functionality was tested running menu item 1 followed by 2 from main, and verifying the readout.

####Exercise 1.1.2 Updating printout
This update has much the same form as the previous, just using the begin() and end() from the pro-
duct list for the copy source, and an ostream_itterator constructed from cout as the target itterator.
Menu item 2 of main is used to test this.
    
####Exercise 1.1.3 Adding an item
The function takes the necessary values from cin and updates the product database.
Menu item 3 followed by 2 allows verification.

####Exercise 1.1.4 Writing product list to file
Again more or less the same procedure is employed. The source is the pl.begin() and pl.end() it-
terators, and the target is an ostream_itterator created from an ofstream object using the path.
The previous contents are automatically deleted when using an ofstream in the default configuration.
A newline charactor is passed to the itterator, to be inserted between elements.
Tested using menu item 1, then 3, then 4 and verifying the file with less.

###Exercise 1.2 Algorithmic manipulations
####Exercise 1.2.1 Too few items sold
We used the function `std::remove_copy_if()` by giving it the stard and end of our productlist,
an iterator to print directly to `std::cout` and a struct that implements the comparison of an
arbitrary sales value with the product list sales, copying only the ones qualifying as badly
selling products.

###Exercise 1.2.2 Discount

####Exercise 1.2.2.1 Using for_each
Using std::for_each to apply the discount, all that is needed is a functor taking a single product
reference, and applying a discount to it's price. The discount is given to the functor through the 
constructor. The struct DiscountFunctor is defined above the function implementation, and simply 
takes a discount percentage in the constructor which is saved as a price conversion factor, that is
then applied to the product price in the operator overload.
Having the functor, the addDiscountUsingForEach consists of only one line, namely the call to 
std::for_each.
NB: I added the discount to the function prototypes and to the main, so that the function can be 
    tested for user defined discount values.

####Exercise 1.2.2.2 Using transform
Using transform the functor needs to return a new Product object, since it doesn't modify the objects
in place. The second functor struct is placed right after the other, and it can be seen that the im-
plementation is almost the same, only using the copy constructor to make a new object first. 
The addDiscountUsingTransform implementation contains a few output lines, but the actual functional
-ity is again contained in a single line containing the call to transform. The only two differences
from the foreach approach is the different functor, and the fact that there's a target itterator, in
this case being a ostream_itterator created from cout with a newline added between each element.

