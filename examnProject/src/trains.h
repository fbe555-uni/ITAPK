//
// Created by felix on 10/17/16.
//

#ifndef CMS_TRAINS_H
#define CMS_TRAINS_H

#include <boost/mpl/list.hpp>
#include "cargo.h"

namespace CMS{
    //Locomotive:
    template<double capacity>
    struct Locomotive<capacity>{
        Locomotive() : _capacity(capacity){}
        double _capacity;
    };
/*
    //Carriage:
    template<CargoType ct, boost::mpl::list L>
    IS_VALID_TANKER_CARRIAGE<ct,
    template<boost::mpl::list>
*/


}

#endif //CMS_TRAINS_H
