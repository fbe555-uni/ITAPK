#include <iostream>
#include <boost/signals2.hpp>
#include <thread>
#include "trains.hpp"
#include "station.hpp"
#include "CMS.hpp"
//#include "SimulationController.hpp"

int main() {
    std::list<cm::Train> trains;
    trains.push_back(cm::Train());
    trains.push_back(cm::Train());
    trains.push_back(cm::Train());

    cm::CMS cms = cm::CMS();
    SimulationController(&cms,trains);
    return 0;
}