#include <iostream>
#include "MyArray.h"
int main() {
    felhak::MyArray<int, 10> myArray;
    myArray.fill(3);


    std :: cout << "Looking for '3'? " << (  felhak::myfind(myArray.begin(),myArray.end(),3) !=
                                             myArray.end ()? "found " : "sry no") << std :: endl;

    std::cout << "the size of our array is: " << myArray.size() << std::endl;
    std::cout << "this is index number 4's value: " << myArray[4] << std::endl;
    return 0;
}