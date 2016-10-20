#include <iostream>
#include <boost/signals2.hpp>
#include <thread>
#include "trains.hpp"
#include "station.hpp"
#include "CMS.hpp"

//#include "SimulationController.hpp"

int main() {
    std::list<cm::Train::Ptr> trains;
    trains.push_back(cm::Train::Ptr(new cm::Train()));
    trains.push_back(cm::Train::Ptr(new cm::Train()));
    trains.push_back(cm::Train::Ptr(new cm::Train()));
    trains.push_back(cm::Train::Ptr(new cm::Train()));

    cm::CMS cms("Test Station", 3);

    SimulationController sc(&cms);

    sc.startSimulation(trains);
    return 0;
}
