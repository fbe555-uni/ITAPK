#include <iostream>
#include "SharedPtr.h"
#include "test_class.h"
using felhak::SharedPtr;

struct CustomDestruct{
    void operator()(int* i){
        std::cout << "super custom" << *i << std::endl;
    }
};

int main() {
    //constructor tests:
    SharedPtr<TestClass> *my1stPtr = new SharedPtr<TestClass>(new TestClass("FirstClass"));
    SharedPtr<TestClass> my2ndPtr = *my1stPtr;
    SharedPtr<TestClass> *my3rdPtr = new SharedPtr<TestClass>(my2ndPtr);

    std::cout << "count: " << my1stPtr->count() << std::endl;
    delete my1stPtr;
    std::cout << "count: " << my2ndPtr.count() << std::endl;
    my2ndPtr = SharedPtr<TestClass>(new TestClass("NotFirstClass"));
    std::cout << "count: " << my3rdPtr->count() << std::endl;
    delete my3rdPtr;

    //overload tests:
    typedef struct TestStruct{
      std::string a = "hello";
      std::string b = "world";
    } TestStruct;

    SharedPtr<TestStruct> mySharedPtr = SharedPtr<TestStruct>(new TestStruct());
    std::cout << "(*mySharedPtr).a << (*mySharedPtr).b returned: " << (*mySharedPtr).a << (*mySharedPtr).b << std::endl;
    std::cout << "mySharedPtr->a << mySharedPtr->b returned: " << mySharedPtr->a << mySharedPtr->b << std::endl;

    std::cout << "testing custom destructor:";
    SharedPtr<int>* cDestrShPtr = new SharedPtr<int>(new int(5), CustomDestruct());
    delete(cDestrShPtr);
    return 0;
}