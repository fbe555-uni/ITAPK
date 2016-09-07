//
// Created by huxx on 8/29/16.
//

#ifndef SHARED_PTR_SHAREDPTR_H
#define SHARED_PTR_SHAREDPTR_H

#include <glob.h>

namespace felhak {

    namespace details{
        template <typename T>
        struct ShPtrHelper{
            virtual void operator()(T* t) = 0;
            virtual ~ShPtrHelper(){}
        };

        template <typename T, typename D>
        struct ShPtrHelperImpl : public ShPtrHelper<T>{
            ShPtrHelperImpl(D d) : _d(d){};
            void operator()(T* t){
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
        }

        template<typename D>
        SharedPtr(T *t, D d) : SharedPtr(t){
            _h = new details::ShPtrHelperImpl<T, D>(d);
        };

        SharedPtr(const SharedPtr &other) {
            ptr = other.ptr;
            count_ptr = other.count_ptr;
            *count_ptr += 1;
        }

        SharedPtr& operator=(const SharedPtr &other) {
            //TODO add self check
            *count_ptr -= 1;
            if (*count_ptr == 0) {
                delete ptr;
                delete count_ptr;
            }
            ptr = other.ptr;
            count_ptr = other.count_ptr;
            *count_ptr += 1;
            return *this;
        }

        ~SharedPtr() {
            *count_ptr -= 1;
            if (*count_ptr == 0) {
                if(_h){
                    (*_h)(ptr);
                }else{
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

        virtual const bool operator!=(const SharedPtr &other) {
            return ptr != other.ptr;
        }

        size_t count() const {

            return *count_ptr;
        }


    private:
        T *ptr;
        details::ShPtrHelper<T>* _h;
        size_t *count_ptr;
    };
}

#endif //SHARED_PTR_SHAREDPTR_H
