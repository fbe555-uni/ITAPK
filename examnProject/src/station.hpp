//
// Created by felix on 10/17/16.
//
#include <list>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <queue>
#include "trains.hpp"
#include "cargo.hpp"

#ifndef CMS_STATION_H
#define CMS_STATION_H

namespace cm {


    class Platform {
    public:
        Platform();
        //Platform(const cm::Platform&);

        void Status(); // Tells if a platform is occupied.
        std::string getID();

        cm::Train::Ptr getTrain();

        std::list<cm::Cargo::Ptr> getCargoList();

        //returns false if there is already a train
        bool trainArrive(cm::Train::Ptr);

        cm::Train::Ptr trainDepart();

        bool isFree();
    private:
        static int num_id;
        std::string ID;
        cm::Train::Ptr _train;
        std::list<cm::Cargo::Ptr> _cargo;
    };

    inline std::ostream &operator<<(std::ostream &out, Platform &platform) {
        out << platform.getID();
        return out;
    }


    class Station {
    public:
        Station(std::string, int);

        void Status(); // Lists platforms and their status
        std::string* getName();

        std::list<Platform> *getPlatforms();
        std::queue<cm::Train::Ptr>* getTrainQueue();
        bool isFull();
    private:
        std::queue<cm::Train::Ptr> trainQueue;
        std::list<Platform> platforms;
        std::string name;
    };

    inline std::ostream &operator<<(std::ostream &out, Station &station) {
        out << station.getName();
        return out;
    }



}

#endif //CMS_STATION_H
