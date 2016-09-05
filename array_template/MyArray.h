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

        template<typename D>
        MyArray(MyArray<D, s> orig){
            array = new T[s];
            T* i = begin();
            D* j = orig.begin();
            while(i != end()){
                *i = *j;
                i++;
                j++;
            }
        }

        template <typename D>
        MyArray<T, s>& operator=(MyArray<D, s> orig){
            T* i = begin();
            D* j = orig.begin();
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

        T *begin() {
            return array;
        }

        T *end() {
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

    template <typename T, typename D>
    T* myfind (T* first , T* last , const D& v){
        for(;first != last; first++){
            if(*first == v) return first;
        }
        return last;
    }
}

#endif //ARRAY_TEMPLATE_H
