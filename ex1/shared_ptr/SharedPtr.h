//
// Created by huxx on 8/29/16.
//

#ifndef SHARED_PTR_SHAREDPTR_H
#define SHARED_PTR_SHAREDPTR_H

#include <glob.h>

namespace felhak {

    namespace details {
        template<typename T>
        struct ShPtrHelper {
            virtual void operator()(T *t) = 0;
            virtual ~ShPtrHelper() {}
        };

        template<typename T, typename D>
        struct ShPtrHelperImpl : public ShPtrHelper<T> {
            ShPtrHelperImpl(D d) : _d(d) {};

            void operator()(T *t) {
                _d(t);
            }

            D _d;
        };
    }

    template<typename T>
    class SharedPtr {
    public:
        //explicit constructor
        explicit SharedPtr(T *t) {
            ptr = t;
            count_ptr = new size_t;
            *count_ptr = 1;
            _h = NULL;
        }

        template<typename D>
        SharedPtr(T *t, D d) : SharedPtr(t) {
            _h = new details::ShPtrHelperImpl<T, D>(d);
        };

        SharedPtr(const SharedPtr &other) : ptr(other.ptr), count_ptr(other.count_ptr) {
            if (other._h) {
                *_h = *other._h;
            }
            *count_ptr += 1;
        }

        SharedPtr &operator=(const SharedPtr &other) {
            if (other.ptr == ptr) return *this;
            *count_ptr -= 1;
            if (*count_ptr == 0) {
                delete ptr;
                delete count_ptr;
            }
            ptr = other.ptr;
            count_ptr = other.count_ptr;
            *count_ptr += 1;
            if (other._h) {
                *_h = *other._h;
            }
            return *this;
        }

        ~SharedPtr() {
            *count_ptr -= 1;
            if (*count_ptr == 0) {
                if (_h) {
                    (*_h)(ptr);
                } else {
                    delete ptr;
                }
                delete _h;
                delete count_ptr;
            }
        }

        //behave like normal pointer when using the shared ptr
        T &operator*() const {

            return *ptr;
        }

        //behave like normal pointer when using the shared ptr
        T *operator->() const {

            return ptr;
        }

        size_t count() const {

            return *count_ptr;
        }


    private:
        T *ptr;
        details::ShPtrHelper<T> *_h = NULL;
        size_t *count_ptr;
    };

    template<typename T, typename U>
    bool operator==(const SharedPtr<T> &a, const SharedPtr<U> &b) {
        return &(*a) == &(*b);
    }

    template<typename T, typename U>
    bool operator!=(const SharedPtr<T> &a, const SharedPtr<U> &b) {
        return &(*a) != &(*b);;
    }

}

#endif //SHARED_PTR_SHAREDPTR_H
