//
// Created by felix on 10/17/16.
//

#ifndef CMS_CARGO_H
#define CMS_CARGO_H

#include <ratio>
#include <iostream>

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
        Cargo(CargoType ct, int w) : cargoType(ct), weight(w), loadTime(1)
        {
            //if(IS_LIQUID<cargoType>::value) loadTime = weight*LIQUID_LOAD_FACTOR;
            //else if(IS_LIVESTOCK<cargoType>::value) loadTime = weight * LIVESTOCK_LOAD_FACTOR;
            //else loadTime = weight*BASE_LOAD_FACTOR;
        }

        const CargoType cargoType;
        const int weight;
        int loadTime;
    };

    std::ostream& operator<<(std::ostream& out, const Cargo& cargo){
        out << cargo.weight << " kg of ";
        switch(cargo.cargoType){
            case TIMBER:
                out << "timber";
                break;
            case COAL:
                out << "coal";
                break;
            case GRAINS:
                out << "grains";
                break;
            case OIL:
                out << "oil";
                break;
            case GASOLINE:
                out << "gasoline";
                break;
            case WATER:
                out << "water";
                break;
            case SHEEP:
                out << "sheep";
                break;
            case COWS:
                out << "cows";
                break;
            case PIGS:
                out << "pigs";
                break;
            default:
                out << "XXX";
                break;
        }
        out << " (" << cargo.loadTime << "s needed for loading)";
    }

};
#endif //CMS_CARGO_H
