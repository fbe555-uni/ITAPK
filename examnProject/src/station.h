//
// Created by felix on 10/17/16.
//
#include <list>
#include <iostream>
#include "trains.h"
#include "cargo.h"

#ifndef CMS_STATION_H
#define CMS_STATION_H

namespace CMS{
    class Station{
    public:
        void Status(); // Lists platforms and their status
    private:
        std::list<Platform> _platforms;
    };

    class Platform{
    public:
        Platform();
        void Status(); // Tells if a platform is occupied.
    private:
        Train _train;
        std::list<Cargo> _cargo;
    };
}

#endif //CMS_STATION_H
