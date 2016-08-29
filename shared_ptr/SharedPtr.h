//
// Created by huxx on 8/29/16.
//

#ifndef SHARED_PTR_SHAREDPTR_H
#define SHARED_PTR_SHAREDPTR_H

#include <glob.h>

template <typename T>
class SharedPtr {
public:
    SharedPtr(T* t) {
        ptr = t;
        count_ptr = new size_t;
        *count_ptr = 1;
    }

    SharedPtr(const SharedPtr& other){
        ptr = other.ptr;
        count_ptr = other.count_ptr;
        *count_ptr += 1;
    }

    SharedPtr& operator=(const SharedPtr& other){
        ptr = other.ptr;
        count_ptr = other.count_ptr;
        *count_ptr += 1;
        return (SharedPtr &) this;
    }

    ~SharedPtr() {
        *count_ptr -= 1;
        if (*count_ptr == 0){
            delete ptr;
            delete count_ptr;
        }
    }

    const T& operator*(){

        return &(*ptr);
    }

    const T* operator->(){

        return ptr;
    }

    const size_t count(){

        return *count_ptr;
    }

private:
    T* ptr;
    size_t* count_ptr;
};


#endif //SHARED_PTR_SHAREDPTR_H
