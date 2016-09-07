//
// Created by huxx on 8/29/16.
//

#ifndef SHARED_PTR_TEST_CLASS_H
#define SHARED_PTR_TEST_CLASS_H
#include <iostream>

class TestClass {
public:
    TestClass(std::string other_string){
        _string = other_string;
        std::cout << "class: " << _string << " has been created" << std::endl;
    }

    ~TestClass(){
        std::cout << "class: " << _string << " has been destroyed" << std::endl;
    }

private:
    std::string _string;
};


#endif //SHARED_PTR_TEST_CLASS_H
