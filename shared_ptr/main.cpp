#include <iostream>
#include "SharedPtr.h"

int main() {
    std::string hello_world = "Hello World";
    SharedPtr<std::string, int> mySharedPtr = SharedPtr<std::string, int>(&hello_world);

    return 0;
}