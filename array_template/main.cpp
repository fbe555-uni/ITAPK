#include <iostream>
#include "MyArray.h"
int main() {
    felhak::MyArray<double, 10> myArray;
    myArray.fill(3);


    std :: cout << "Looking for '3'? " << (  felhak::myfind(myArray.begin(),myArray.end(),3) !=
                                             myArray.end ()? "found " : "sry no") << std :: endl;

    std::cout << "the size of our array is: " << myArray.size() << std::endl;
    std::cout << "this is index number 4's value: " << myArray[4] << std::endl;

    felhak::MyArray<int, 10> myIntArray(myArray);
    std::cout << "length of new array is: " << myIntArray.size() << std::endl;
    std::cout << "contents:";
    for(int* i = myIntArray.begin(); i != myIntArray.end(); i++){
        std::cout << " " << *i;
    }
    std::cout << std::endl;
    myIntArray.fill(5);
    myArray = myIntArray;
    std::cout << "myArray after assignment:";
    for(double* i = myArray.begin(); i != myArray.end(); i++){
        std::cout << " " << *i;
    }
    std::cout << std::endl;

    return 0;
}