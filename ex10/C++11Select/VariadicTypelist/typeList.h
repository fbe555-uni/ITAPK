//
// Created by felix on 9/28/16.
//

#ifndef C11_SELECT_TYPELIST_H
#define C11_SELECT_TYPELIST_H

struct NullType{};

template<typename T, typename ... Rest>
struct TypeList{
    typedef T F;
    typedef TypeList<Rest> R;
};

template<typename T>
struct TypeList{
    typedef T F;
    typedef NullType R;
};

template<typename T1, typename T2>
struct IsSame{
    static const bool value = false;
};

template<typename T>
struct IsSame<T, T>{
    static const bool value = true;
};

template<typename TL, typename T>
struct Contains{
    static const bool value = IsSame<TL::F, T>::value || Contains<TL::R, T>::value;
};

template<typename T>
struct Contains<NullType, typename T>{
    static const bool value = false;
};
#endif //C11_SELECT_TYPELIST_H

