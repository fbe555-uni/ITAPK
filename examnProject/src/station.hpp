//
// Created by felix on 10/17/16.
//
#include <list>
#include <iostream>
#include <boost/shared_ptr.hpp>
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
        std::string getID() {
            return ID;
        };

        bool isFree() {
            if (!_train) return true;
            else return false;
        }

        cm::Train::Ptr getTrain() {
            return _train;
        }

        //returns false if there is already a train
        bool trainArrive(cm::Train::Ptr);

        //returns false if there is no train to remove
        cm::Train::Ptr trainDepart();

    private:
        static int num_id;
        std::string ID;
        cm::Train::Ptr _train;
        std::list<cm::Cargo> _cargo;
    };

    inline std::ostream &operator<<(std::ostream &out, Platform &platform) {
        out << platform.getID();
        return out;
    }

    class Station {
    public:
        Station(std::string, int);

        void Status(); // Lists platforms and their status
        std::string getName() {
            return _name;
        }

        std::list<Platform> *getPlatforms();

    private:
        std::list<Platform> _platforms;
        std::string _name;
    };

    inline std::ostream &operator<<(std::ostream &out, Station &station) {
        out << station.getName();
        return out;
    }

    //TODO finish trainQueue
    class TrainQueue {

        std::list<std::shared_ptr<Train>> trains;
    };

}

#endif //CMS_STATION_H
