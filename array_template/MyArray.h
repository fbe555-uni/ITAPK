//
// Created by huxx on 8/29/16.
//

#include <glob.h>

#ifndef ARRAY_TEMPLATE_MYARRAY_H
#define ARRAY_TEMPLATE_MYARRAY_H
namespace felhak {

    template<typename T, size_t size_>
    class MyArray {
    public:
        MyArray(){
            array = new T[size_];
        }

        template<typename D>
        MyArray(MyArray<D, size_t> orig){
            array = new T[orig.size()];
            _size = orig.size();
            T* i = begin();
            D* j = orig.begin();
            while(i != end()){
                *i = *j;
                i++;
                j++;
            }
        }

        template <typename D>
        operator=(MyArray<D, size_t> orig){
            if(_size != orig.size()) {
                array = new T[orig.size()];
                _size = orig.size();
                T* i = begin();
                D* j = orig.begin();
                while(i != end()){
                    *i = *j;
                    i++;
                    j++;
                }
            }
        }

        ~MyArray() {
            delete array;
        }

        void fill(const T & value) {
            for(T* i = begin(); i != end(); i++){
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
        size_t _size = size_;
        T* array;
    };

    template <typename T>
    T* myfind (T* first , T* last , const T& v){
        for(;first != last; first++){
            if(*first == v) return first;
        }
        return last;
    }
}
