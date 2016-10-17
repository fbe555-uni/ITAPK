//
// Created by felix on 10/17/16.
//

#ifndef CMS_CARGO_H
#define CMS_CARGO_H

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
    template <CargoType ct>
    struct IS_LIQUID<ct>{
        static bool value = false;
    };

    struct IS_LIQUID<OIL>{
        static bool value = true;
    };

    struct IS_LIQUID<GASOLINE>{
        static bool value = true;
    };

    struct IS_LIQUID<WATER>{
        static bool value = true;
    };


    template <CargoType ct>
    struct IS_LIVESTOCK<ct>{
        static bool value = false;
    };

    struct IS_LIVESTOCK<SHEEP>{
        static bool value = true;
    };

    struct IS_LIVESTOCK<COWS>{
        static bool value = true;
    };

    struct IS_LIVESTOCK<PIGS>{
        static bool value = true;
    };

    //Cargo struct
    struct Cargo{
        Cargo(CargoType ct, double weight) : _cargoType(ct), _weight(weight)
        {
            if(IS_LIQUID<_cargoType>::value) _loadTime = _weight * LIQUID_LOAD_FACTOR;
            else if(IS_LIVESTOCK<_cargoType>::value) _loadTime = _weight * LIVESTOCK_LOAD_FACTOR;
            else _loadTime = _weight * BASE_LOAD_FACTOR;
        }

        CargoType _cargoType;
        double _weight;
        double _loadTime;
    };

};
#endif //CMS_CARGO_H
