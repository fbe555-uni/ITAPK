//
// Created by huxx on 8/29/16.
//

#include <glob.h>

#ifndef ARRAY_TEMPLATE_MYARRAY_H
#define ARRAY_TEMPLATE_MYARRAY_H
namespace felhak {

    template<typename T, size_t size>
    class MyArray {
    public:
        MyArray(){}

        ~MyArray() {}

        void fill(const T & value) {
            T* i = begin();
            for(; i != end(); i++){
                *i = value;
            }
        }

        T *begin() const {
            return array;
        }

        T *end() const {
            return array+_size;
        }

        T& operator[](int i) {
            return *(array+i);
        }

        size_t size() const {
            return _size;
        }

    private:
        size_t _size = size;
        T array[size];
    };

    template <typename T>
    T* myfind (T* first , T* last , const T& v){
        for(;first != last; first++){
            if(*first == v) return first;
        }
        return nullptr;
    }
}
