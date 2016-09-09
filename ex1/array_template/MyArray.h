//
// Created by huxx on 8/29/16.
//

#include <glob.h>

#ifndef ARRAY_TEMPLATE_MYARRAY_H
#define ARRAY_TEMPLATE_MYARRAY_H
namespace felhak {

    template<typename T, size_t s>
    class MyArray {
    public:
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

        T *begin() const{
            return array;
        }

        T *end() const{
            return array+_size;
        }

        T& operator[](int i) {
            return *(array+i);
        }

        size_t size() const {
            return _size;
        }

    private:
        size_t _size = s;
        T* array;
    };

    template <typename T, size_t s>
    class MyArray<T*, s>{
    public:
        MyArray(){
            array = new T[s];
        }

        template<typename U>
        MyArray(const MyArray<U, s>& orig){
            array = new T[s];
            T** i = begin();
            U* j = orig.begin();
            while(i != end()){
                *i = *j;
                i++;
                j++;
            }
        }

        template <typename U>
        MyArray<T, s>& operator=(const MyArray<U, s>& orig){
            T** i = begin();
            U* j = orig.begin();
            while(i != end()){
                *i = *j;
                i++;
                j++;
            }
            return *this;
        }

        ~MyArray() {
            for(T** i = begin(); i != end(); i++){
                delete *i;
            }
            delete [] array;
        }

        void fill(const T & value) {
            for(T** i = begin(); i != end(); i++){
                *i = value;
            }
        }

        T *begin() const{
            return array;
        }

        T *end() const{
            return array+_size;
        }

        T& operator[](int i) {
            return *(array+i);
        }

        size_t size() const {
            return _size;
        }

    private:
        size_t _size = s;
        T* array;
    };

    template <typename T, typename U>
    T* myfind (T* first , T* last , const U& v){
        for(;first != last; first++){
            if(*first == v) return first;
        }
        return last;
    }
    template < typename T, typename V>
    T** myfind (T** first , T** last , const V& v){
        for(;first != last; first++){
            if(**first == v) return first;
        }
        return last;
    };
}

#endif //ARRAY_TEMPLATE_H
