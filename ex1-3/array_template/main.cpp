#include <iostream>
#include "MyArray.h"
#include <vector>


//*********** container utility functions *************
template < typename U>
typename U:: value_type myAccumulation ( const U& u) {
    typename U::value_type m = typename U::value_type();
    for (auto first = u.begin(); first != u.end(); ++first) {
        m += *first;
    }
    return m;
}
template <typename T, typename U>
T* myfind (T* first , T* last , const U& v){
    for(;first != last; first++){
        if(*first == v) return first;
    }
    return last;
}
template < typename T, typename V>
T** myfind (T** first , T** last , const V& v){
    for(;first != last; first++){

        if(*first && **first == v) return first;
    }
    return last;
};
//******************** main **************************

int main() {
    //class test
    {
        felhak::MyArray<double, 10> myArray;
        myArray.fill(3);


        std::cout << "Looking for '3'? " << (myfind(myArray.begin(), myArray.end(), 3.1) !=
                                             myArray.end() ? "found " : "sry no") << std::endl;

        std::cout << "the size of our array is: " << myArray.size() << std::endl;
        std::cout << "this is index number 4's value: " << myArray[4] << std::endl;

        felhak::MyArray<int, 10> myIntArray(myArray);
        std::cout << "length of new array is: " << myIntArray.size() << std::endl;
        std::cout << "contents:";
        for (int *i = myIntArray.begin(); i != myIntArray.end(); i++) {
            std::cout << " " << *i;
        }
        std::cout << std::endl;
        myIntArray.fill(5);
        myArray = myIntArray;
        felhak::MyArray<double, 10> myNewArray(myIntArray);
        std::cout << "myArray after assignment:";
        for (double *i = myArray.begin(); i != myArray.end(); i++) {
            std::cout << " " << *i;
        }
        std::cout << std::endl;
    }
    // myAccumulation test
    {
        std::vector<int> myVector = {1, 2, 3, 4, 5};
        felhak::MyArray<int, 5> myArray;
        myArray.fill(1);
        std::cout << "myAccumulation(myVector) (should be 15): " << myAccumulation(myVector) << std::endl;
        std::cout << "myAccumulation(myArray) (should be 5): " << myAccumulation(myArray) << std::endl;
    }

    //partial specialisation test
    {
        felhak::MyArray<std::string*,5> my;
        my [5] = new std::string ("Hello"); // Assuming that my is a MyArray of string pointers
        std::cout << *my[5] << std::endl;
        std :: cout << " Looking for 'Hello'? " << ( myfind (my.begin (), my.end (),
                                                              std :: string ("Hello")) != my.end ()? " found " : "sry no") << std :: endl;

    }
    return 0;
}