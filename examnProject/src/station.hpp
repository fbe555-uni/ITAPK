//
// Created by felix on 10/17/16.
//
#include <list>
#include <iostream>
#include "trains.hpp"
#include "cargo.hpp"

#ifndef CMS_STATION_H
#define CMS_STATION_H

namespace ST3000{

    class Platform{
    public:
        Platform();
        void Status(); // Tells if a platform is occupied.
        std::string getID(){
                return ID;
        };
    private:
        static int id;
        std::string ID;
        Train _train;
        std::list<Cargo>* _cargo;
    };

    inline std::ostream& operator<<(std::ostream& out, Platform& platform){
        out << platform.getID();
        return out;
    }

    class Station{
    public:
        Station(std::string n);
        void Status(); // Lists platforms and their status
        std::string getName(){
            return _name;
        }
    private:
        std::list<Platform> _platforms;
        std::string _name;
    };

    inline std::ostream& operator<<(std::ostream& out, Station& station){
        out << station.getName();
        return out;
    }

}

#endif //CMS_STATION_H
