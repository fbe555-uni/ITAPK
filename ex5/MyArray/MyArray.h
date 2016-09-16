#include <glob.h>

#ifndef ARRAY_TEMPLATE_MYARRAY_H
#define ARRAY_TEMPLATE_MYARRAY_H
namespace felhak {

    template<typename T>
    class MyArray_iterator : public std::iterator<std::random_access_iterator_tag, T>{
    private:
        T* _ptr;
    public:
        MyArray_iterator() : _ptr(NULL) {}
        MyArray_iterator(T* ptr) : _ptr(ptr) {}

        MyArray_iterator(const MyArray_iterator<T>& it) : _ptr(it._ptr){}

        MyArray_iterator& operator++() {++_ptr;return *this;}
        MyArray_iterator& operator--() {--_ptr;return *this;}
        MyArray_iterator operator++(int) {MyArray_iterator tmp(*this); operator++(); return tmp;}
        MyArray_iterator operator--(int) {MyArray_iterator tmp(*this); operator--(); return tmp;}

        MyArray_iterator& operator+(int i) {_ptr += i; return *this;}
        MyArray_iterator& operator-(int i) {_ptr -= i; return *this;}
        int operator-(const MyArray_iterator<T>& it) {return _ptr-it._ptr;}

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

    template <typename T>
    MyArray_iterator<T>& operator+(int i, MyArray_iterator<T>& it) {return it+i;}

    template<typename T, size_t s>
    class MyArray {
    private:
        T* ptr;

    public:
        typedef T value_type;

        MyArray(){
            array = new T[s];
        }

        template<typename U>
        MyArray(const MyArray<U, s>& orig){
            array = new T[s];
            MyArray_iterator<T> i = begin();
            MyArray_iterator<U> j = orig.begin();
            while(i != end()){
                *i = *j;
                i++;
                j++;
            }
        }

        template <typename U>
        MyArray<T, s>& operator=(const MyArray<U, s>& orig){
            MyArray_iterator<T> i = begin();
            MyArray_iterator<U> j = orig.begin();
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
            for(MyArray_iterator<T> i = begin(); i != end(); i++){
                *i = value;
            }
        }

        MyArray_iterator<T> begin() const{
            return MyArray_iterator<T>(array);
        }

        MyArray_iterator<const T> cbegin() const{
            return MyArray_iterator<const T>(array);
        }

        MyArray_iterator<T> end() const{
            return MyArray_iterator<T>(array+_size);
        }

        MyArray_iterator<const T> cend() const{
            return MyArray_iterator<const T>(array+_size);
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
