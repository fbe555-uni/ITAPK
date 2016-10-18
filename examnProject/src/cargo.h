//
// Created by felix on 10/17/16.
//

#ifndef CMS_CARGO_H
#define CMS_CARGO_H

#include <ratio>
#include <iostream>
#include <typeinfo>
#include <string.h>


namespace CMS{

    //Constants
    const double BASE_LOAD_FACTOR = 1;
    const double LIQUID_LOAD_FACTOR = 0.5;
    const double LIVESTOCK_LOAD_FACTOR = 2;

    //Cargo struct
    class Cargo{
    public:
        Cargo(int w, int lt) : weight(w), loadTime(lt)
        {
        }

        virtual ~Cargo(){}

        const int weight;
        const int loadTime;
    };

    class Timber : public Cargo{
        Timber(int w): Cargo(w, BASE_LOAD_FACTOR*w){}
        ~Timber(){};
    };

    class Coal : public Cargo{
        Coal(int w): Cargo(w, BASE_LOAD_FACTOR*w){}
        ~Coal(){};
    };

    class Grains : public Cargo{
        Grains(int w): Cargo(w, BASE_LOAD_FACTOR*w){}
        ~Grains(){};
    };

    class Oil : public Cargo{
        Oil(int w): Cargo(w, LIQUID_LOAD_FACTOR*w){}
        ~Oil(){};
    };

    class Gasoline: public Cargo{
        Gasoline(int w): Cargo(w, LIQUID_LOAD_FACTOR*w){}
        ~Gasoline(){};
    };

    class Water: public Cargo{
        Water(int w): Cargo(w, LIQUID_LOAD_FACTOR*w){}
        ~Water(){};
    };

    class Sheep : public Cargo{
        Sheep(int w): Cargo(w, LIVESTOCK_LOAD_FACTOR*w){}
        ~Sheep(){};
    };

    class Cows : public Cargo{
        Cows(int w): Cargo(w, LIVESTOCK_LOAD_FACTOR*w){}
        ~Cows(){};
    };

    class Pigs : public Cargo{
        Pigs(int w): Cargo(w, LIVESTOCK_LOAD_FACTOR*w){}
        ~Pigs(){};
    };

    inline std::ostream& operator<<(std::ostream& out, Cargo const* cargo){
        out << cargo->weight << " kg of " << typeid(*cargo).name();
        out << " (" << cargo->loadTime << "s needed for loading)";
        return out;
    }

    /*******************************************************************
     **             TMP EVALUATION/CONDITION STRUCTS                  **
     *******************************************************************/
    template <typename CT>
    struct IS_LIQUID_CARGO{
        static const bool value = false;
    };

    template <>
    struct IS_LIQUID_CARGO<Oil>{
        static const bool value = true;
    };

    template <>
    struct IS_LIQUID_CARGO<Gasoline>{
        static const bool value = true;
    };

    template <>
    struct IS_LIQUID_CARGO<Water>{
        static const bool value = true;
    };


    template <typename CT>
    struct IS_LIVESTOCK_CARGO{
        static const bool value = false;
    };

    template <>
    struct IS_LIVESTOCK_CARGO<Sheep>{
        static const bool value = true;
    };

    template <>
    struct IS_LIVESTOCK_CARGO<Cows>{
        static const bool value = true;
    };

    template <>
    struct IS_LIVESTOCK_CARGO<Pigs>{
        static const bool value = true;
    };

    // is same type tmp boolean
    template<typename T, typename U>
    struct IS_SAME_TYPE{
        static const bool value = false;
    };

    template<typename T>
    struct IS_SAME_TYPE<T, T>{
        static const bool value = true;
    };

    //TODO: check if works for subclasses else: std::is_base_of<Cargo, H>
    template<typename T>
    struct IS_CARGO{
        static const bool value = IS_SAME_TYPE<Cargo, T>::value;
    };

    /*******************************************************************
     **                    TMP CARGOLIST STRUCTS                      **
     *******************************************************************/
    class CL_NULL_ELEM{};

    template<typename H, typename T>
    struct CL{
        typedef H HEAD;
        typedef T TAIL;
    };

    template<typename H>
    struct CL<H, CL_NULL_ELEM>{
        typedef H HEAD;
        typedef CL_NULL_ELEM TAIL;
    };

    template<typename first, typename ... rest>
    struct CARGO_LIST{
        typedef CL<first, CL<rest...> > LIST;
    };

    /*******************************************************************
     **                      Cargolist utilities                      **
     *******************************************************************/
/*
    template<typename CL, typename T>
    struct CL_CONTAINS{
        static const bool value = IS_SAME_TYPE<typename CL::LIST::HEAD, T>::value || CL_CONTAINS<typename CL::LIST::TAIL, T>::value;
    };

    template<typename T>
    struct Cl_CONTAINS<CL_NULL_ELEM, T>{
        static const bool value = false;
    };

    template<typename CL, typename CONDITION>
    struct CL_AND_CONDITION{
        static const bool value = CONDITION<CL::LIST::HEAD>::Value && CL_AND_CONDITION<CL::LIST::TAIL, CONDITION>::value;
    };

    template<typename CONDITION>
    struct CL_AND_CONDITION<CL_NULL_ELEM, CONDITION>{
        static const bool value = true;
    };

    template<typename CL, typename CONDITION>
    struct CL_OR_CONDITION{
        static const bool value = CONDITION<CL::LIST::HEAD>::Value || CL_OR_CONDITION<CL::LIST::TAIL, CONDITION>::value;
    };

    template<typename CONDITION>
    struct CL_OR_CONDITION<CL_NULL_ELEM, CONDITION>{
        static const bool value = false;
    };

*/

};
#endif //CMS_CARGO_H
