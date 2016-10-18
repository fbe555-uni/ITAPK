//
// Created by felix on 10/17/16.
//

#ifndef CMS_CARGO_H
#define CMS_CARGO_H

#include <ratio>

namespace CMS{

    //Constants
    const double BASE_LOAD_FACTOR = 1;
    const double LIQUID_LOAD_FACTOR = 0.5;
    const double LIVESTOCK_LOAD_FACTOR = 2;

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

    //Cargo struct
    struct Cargo{
        Cargo(CargoType ct, int weight) : _cargoType(ct), _weight(weight)
        {
            if(IS_LIQUID<_cargoType>::value) _loadTime = _weight*LIQUID_LOAD_FACTOR;
            else if(IS_LIVESTOCK<_cargoType>::value) _loadTime = weight * LIVESTOCK_LOAD_FACTOR;
            else _loadTime = weight*BASE_LOAD_FACTOR;
        }

        const CargoType _cargoType;
        const int _weight;
        int _loadTime;
    };

};
#endif //CMS_CARGO_H
