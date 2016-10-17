//
// Created by felix on 10/17/16.
//
#include <list>
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
        void Arrive(); // Whenever a train arrives at a platform it will wend out a signal, occupying this platform
        void Depart(); // Whenever a train leaves a platform it will send out a signal, freeing this platform
        void Status(); // Tells whether a platform is occupied.
    private:
        int _number;
        Train _train;
        std::list<Cargo> _cargo;
    };
}

#endif //CMS_STATION_H
