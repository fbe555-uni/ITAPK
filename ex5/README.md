#STL Algorithms

##Exercise 1 Basic STL

###Exercise 1.1 istream_operator/ostream_operator

####Exercise 1.1.1 Updating file reading
To update the readProductDB function to use std::copy, one needs 3 things: an itterator marking the 
beginning of the source, one marking the end of the source, and one marking the target.
The input begin itterator is obtained by creating an input_itterator<Product> from the file object.
The input end itterator is obtained from the default constructor since this works for EOF. 
####Exercise 1.1.2 Updating printout
    
####Exercise 1.1.3 Adding an item
The function takes the necessary values from cin and updates the product database.