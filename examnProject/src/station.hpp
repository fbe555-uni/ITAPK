//
// Created by felix on 10/17/16.
//
#include <list>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <queue>
#include "trains.hpp"
#include "cargo.hpp"
#include "ThreadSafeCout.hpp"

#ifndef CMS_STATION_H
#define CMS_STATION_H

namespace cm {


    class Platform {
    public:
        Platform();
        void Status() const; // Tells if a platform is occupied.
        std::string getID() const;

        Train::Ptr getTrain();

        std::list<cm::Cargo::Ptr>* getCargoList();
        const std::list<cm::Cargo::Ptr>* getConstCargoList() const;

        void addCargo(std::list<cm::Cargo::Ptr>& cargo);

        bool trainArrive(cm::Train::Ptr);

        Train::Ptr trainDepart();

        bool isFree();

    private:
        static int num_id;
        std::string id;
        cm::Train::Ptr train;
        std::list<cm::Cargo::Ptr> cargo;
    };

    inline std::ostream &operator<<(std::ostream &out, const Platform &platform) {
        out << platform.getID() << " (" << platform.getConstCargoList()->size() << ")";
        return out;
    }

    inline std::ostream &operator<<(std::ostream &out, const Platform* platform) {
        if(platform) return (out << *platform);
        else return out << "!! empty platform pointer !!";
    }



    class Station {
    public:
        Station(std::string, int);

        std::string getName() const;

        std::list<Platform> *getPlatforms();

        std::queue<Train::Ptr> *getTrainQueue();

        bool isFull();

        bool isEmpty();

        bool hasCargo();

        void Status();

    private:
        std::queue<Train::Ptr> trainQueue;
        std::list<Platform> platforms;
        std::string name;
    };

    inline std::ostream &operator<<(std::ostream &out, Station &station) {
        out << station.getName();
        return out;
    }


}

#endif //CMS_STATION_H
