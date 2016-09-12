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