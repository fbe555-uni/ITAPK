//
// Created by huxx on 8/29/16.
//

#include <glob.h>

#ifndef ARRAY_TEMPLATE_MYARRAY_H
#define ARRAY_TEMPLATE_MYARRAY_H
namespace felhak {

    template<typename T>
    class MyArray {
    public:
        MyArray(size_t s){
            _size = s;
        }

        ~MyArray() {

        }

        void fill(const T &) {

        }

        T *begin() const {

        }

        T *end() const {

        }

        T &operator[](int i) {

        }

        size_t size() const {

        }

    private:
        size_t _size;
        T array[];
    };
}
