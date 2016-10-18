//
// Created by felix on 10/17/16.
//

#ifndef CMS_TRAINS_H
#define CMS_TRAINS_H

#include <boost/mpl/list.hpp>
#include "cargo.h"

namespace CMS{
/*
    template<CargoType H, CL T>
    struct CL<H, T>{
        typedef H HEAD;
        typedef T TAIL;
    };

    //Locomotive:
    template<int capacity>
    struct Locomotive{
        Locomotive() : _capacity(capacity){}
        double _capacity;
    };

    template<CargoType first, CargoType ... rest>
    struct CARGO_LIST<first, rest...>{
        typedef CL<first, CL<rest...> > LIST;
    };

    //Carriage:
    template<CargoType ct, boost::mpl::list L>
    IS_VALID_TANKER_CARRIAGE<ct,
    template<boost::mpl::list>

    struct Train{

    };
*/
}

#endif //CMS_TRAINS_H
