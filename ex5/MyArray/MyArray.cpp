//
// Created by felix on 9/16/16.
//

#include "MyArray.h"

namespace felhak {
    MyArray_iterator::MyArray_iterator(): _ptr(nullptr) {}
    MyArray_iterator::MyArray_iterator(T* ptr): _ptr(ptr) {}
    template <typename U, size_t s>
    MyArray_iterator::MyArray_iterator(const MyArray<U, s>& myArray) : MyArray_iterator(myArray.begin()) {}

        template <typename U>
        MyArray_iterator(const MyArray_iterator<U>& it) : _ptr(it._ptr){}

        MyArray_iterator& operator++() {++_ptr;return *this;}
        MyArray_iterator& operator--() {--_ptr;return *this;}
        MyArray_iterator& operator++(int) {MyArray_iterator tmp(*this); operator++(); return tmp;}
        MyArray_iterator& operator--(int) {MyArray_iterator tmp(*this); operator--(); return tmp;}

        MyArray_iterator& operator+(int i) {_ptr += i; return *this;}
        MyArray_iterator& operator-(int i) {_ptr -= i; return *this;}

        bool operator==(const MyArray_iterator& rhs) {return _ptr==rhs._ptr;}
        bool operator!=(const MyArray_iterator& rhs) {return _ptr!=rhs._ptr;}
        bool operator<(const MyArray_iterator& rhs) {return _ptr<rhs._ptr;}
        bool operator<=(const MyArray_iterator& rhs) {return _ptr<=rhs._ptr;}
        bool operator>(const MyArray_iterator& rhs) {return _ptr>rhs._ptr;}
        bool operator>=(const MyArray_iterator& rhs) {return _ptr>=rhs._ptr;}

        T& operator*() {return *_ptr;}
        T& operator->() {return *_ptr;}
        T& operator[](int i) {return *(_ptr+i);}


    };

    template<typename T, size_t s>
    class MyArray {
    private:
        T* ptr;

        typedef T value_type;

        MyArray(){
            array = new T[s];
        }

        template<typename U>
        MyArray(const MyArray<U, s>& orig){
            array = new T[s];
            T* i = begin();
            U* j = orig.begin();
            while(i != end()){
                *i = *j;
                i++;
                j++;
            }
        }

        template <typename U>
        MyArray<T, s>& operator=(const MyArray<U, s>& orig){
            T* i = begin();
            U* j = orig.begin();
            while(i != end()){
                *i = *j;
                i++;
                j++;
            }
            return *this;
        }

        ~MyArray() {
            delete [] array;
        }

        void fill(const T & value) {
            for(T* i = begin(); i != end(); i++){
                *i = value;
            }
        }

        MyArray_iterator<T> *begin() const{
            return MyArray_iterator<T>(array);
        }

        MyArray_iterator<const T> *cbegin() const{
            return MyArray_iterator<const T>(array);
        }

        MyArray_iterator<T> *end() const{
            return MyArray_iterator<T>(array+_size);
        }

        MyArray_iterator<const T> *cend() const{
            return MyArray_iterator<T>(array+_size);
        }

        T& operator[](int const i) {
            return *(array+i);
        }

        size_t size() const {
            return _size;
        }

    private:
        size_t _size = s;
        T* array;
    };
}

#endif //ARRAY_TEMPLATE_H
