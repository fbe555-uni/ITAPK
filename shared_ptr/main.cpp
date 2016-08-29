#include <iostream>
#include "SharedPtr.h"

int main() {
    std::string hello_world = "Hello World";
    SharedPtr<std::string, int> mySharedPtr = SharedPtr<std::string, int>(&hello_world);

    //overload tests:
    typedef struct TestStruct{
      std::string a = "hello"
      std::string b = "world"
    } TestStruct;

    SharedPtr<TestStruct> mySharedPtr = SharedPtr<TestStruct>(TestStruct hw_struct );
    stdout << "(*mySharedPtr).a << (*mySharedPtr).b returned: " << (*mySharedPtr).a << (*mySharedPtr).b << newline;
    stdout << "mySharedPtr->a << mySharedPtr->b returned: " << mySharedPtr->a << mySharedPtr->b << newline;
    
    return 0;
}
