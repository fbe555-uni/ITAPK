#include <iostream>
#include <boost/signals2.hpp>
#include <thread>
#include "trains.hpp"
#include "station.hpp"
#include "CMS.hpp"
//#include "SimulationController.hpp"

int main() {
    std::list<ST3000::Train> trains;
    trains.push_back(ST3000::Train());
    trains.push_back(ST3000::Train());
    trains.push_back(ST3000::Train());

    ST3000::CMS cms = ST3000::CMS();
    SimulationController(&cms,trains);
    return 0;
}