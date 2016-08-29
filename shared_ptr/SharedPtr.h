//
// Created by huxx on 8/29/16.
//

#ifndef SHARED_PTR_SHAREDPTR_H
#define SHARED_PTR_SHAREDPTR_H

#include <glob.h>

template <typename T, typename D>
class SharedPtr {
public:
    //explicit constructor
    explicit SharedPtr(T* t) {
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
        delete this;
        ptr = other.ptr;
        count_ptr = other.count_ptr;
        *count_ptr += 1;
        return (SharedPtr &) this;
    }

    //custom destruction functor
    SharedPtr(T* t, D d) : SharedPtr(t){
        dest_ptr = new D(d);
    }

    ~SharedPtr() {
        *count_ptr -= 1;
        if (*count_ptr == 0){
            delete ptr;
            delete count_ptr;
        }
    }

    //behave like normal pointer when using the shared ptr
    const T& operator*(){

        return &(*ptr);
    }

    //behave like normal pointer when using the shared ptr
    const T* operator->(){

        return ptr;
    }

    virtual const bool operator==(const SharedPtr& lhs, const SharedPtr& rhs){
        return lhs.ptr == rhs.ptr;
    }

    const size_t count(){

        return *count_ptr;
    }

private:
    D* dest_ptr;
    T* ptr;
    size_t* count_ptr;
};


#endif //SHARED_PTR_SHAREDPTR_H
