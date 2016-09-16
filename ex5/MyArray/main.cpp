#include <iostream>
#include "MyArray.h"
#include <vector>
#include <iterator>
#include <numeric>

int main() {
    //class test
    {
        {
            felhak::MyArray<double, 10> myArray;
            myArray.fill(3);

            std::cout << "the size of our array is: " << myArray.size() << std::endl;
            std::cout << "this is index number 4's value: " << myArray[4] << std::endl;

            felhak::MyArray<int, 10> myIntArray(myArray);
            std::cout << "length of new array is: " << myIntArray.size() << std::endl;
            std::cout << "contents:";
            for (felhak::MyArray_iterator<int> i = myIntArray.begin(); i != myIntArray.end(); i++) {
                std::cout << " " << *i;
            }
            std::cout << std::endl;
            myIntArray.fill(5);
            myArray = myIntArray;
            felhak::MyArray<double, 10> myNewArray(myIntArray);
            std::cout << "myArray after assignment:";
            for (felhak::MyArray_iterator<double> i = myArray.begin(); i != myArray.end(); i++) {
                std::cout << " " << *i;
            }
            std::cout << std::endl;
        }
        //************* std algo test ****************
        {
            felhak::MyArray<double, 10> myArray;
            myArray.fill(3);
            std::cout << "will now test the std::copy operator. should output a line with 10 3s" << std::endl;
            std::copy(myArray.cbegin(), myArray.cend(), std::ostream_iterator<double>(std::cout, " "));

            std::cout << std::endl << "Will now test std::accumulate. Should print out 30." << std::endl;
            std::cout << std::accumulate(myArray.begin(), myArray.end(), 0);
        }
    }

    return 0;
}