//
// Created by felix on 10/17/16.
//

#ifndef CMS_CARGO_H
#define CMS_CARGO_H

#include <ratio>

namespace CMS{

    //Constants
    typedef std::ratio<1, 1> BASE_LOAD_FACTOR;
    typedef std::ratio<1, 2> LIQUID_LOAD_FACTOR;
    typedef std::ratio<2, 1> LIVESTOCK_LOAD_FACTOR;

    //Cargo types
    enum CargoType{
        TIMBER,
        COAL,
        GRAINS,
        OIL,
        GASOLINE,
        WATER,
        SHEEP,
        COWS,
        PIGS
    };

    //TMP structs
    template <CargoType CT>
    struct IS_LIQUID{
        static const bool value = false;
    };

    template <>
    struct IS_LIQUID<OIL>{
        static const bool value = true;
    };

    template <>
    struct IS_LIQUID<GASOLINE>{
        static const bool value = true;
    };

    template <>
    struct IS_LIQUID<WATER>{
        static const bool value = true;
    };


    template <CargoType CT>
    struct IS_LIVESTOCK{
        static const bool value = false;
    };

    template <>
    struct IS_LIVESTOCK<SHEEP>{
        static const bool value = true;
    };

    template <>
    struct IS_LIVESTOCK<COWS>{
        static const bool value = true;
    };

    template <>
    struct IS_LIVESTOCK<PIGS>{
        static const bool value = true;
    };

    template <bool Condition, typename TrueResult, typename FalseResult>
    struct TMP_IF;

    template <typename TrueResult, typename FalseResult>
    struct TMP_IF<true, TrueResult, FalseResult>{
        typedef TrueResult Result;
    };

    template <typename TrueResult, typename FalseResult>
    struct TMP_IF<false, TrueResult, FalseResult>{
        typedef FalseResult Result;
    };

    template <CargoType ct, int w>
    struct LOAD_TIME{
        typedef TMP_IF< IS_LIQUID<ct>::value, LIQUID_LOAD_FACTOR, TMP_IF< IS_LIVESTOCK<ct>::value, LIVESTOCK_LOAD_FACTOR, BASE_LOAD_FACTOR >::Result>::Result factor;
        static const int value = factor::num*w/factor::den;
    };

    //Cargo struct
    struct Cargo{
        Cargo(CargoType ct, int weight) : _cargoType(ct), _weight(weight), _loadTime(LOAD_TIME<ct, weight>::value)
        {
        }

        const CargoType _cargoType;
        const int _weight;
        const int _loadTime;
    };

};
#endif //CMS_CARGO_H
