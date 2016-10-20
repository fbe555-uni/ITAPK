//
// Created by felix on 10/17/16.
//

#include "CMS.hpp"

void cm::CMS::setSimulationController(SimulationController *s) {
    SimControl = s;

    SimControl->trainArrivedAtStation.connect([&](cm::Train::Ptr t) {
        ReceiveTrain(t);
    });

    trainFullyLoaded.connect([&](cm::Platform *p) {
        SendTrain(p);
    });
}

cm::CMS::CMS(std::string station_name, int num_platforms) : station(station_name, num_platforms) {
    ID = station.getName() + " -- Cargo controller";
}

std::string cm::CMS::getID() const {
    return ID;
}

void cm::CMS::ReceiveTrain(cm::Train::Ptr train) {
    std::cout << std::endl;
    std::cout << "*********************************************" << std::endl
              << "*** CMS Received train: " << *train << std::endl;
    auto platforms = station.getPlatforms();
    for (auto &platform:*platforms) {
        if (platform.trainArrive(train)) {
            LoadTrain(&platform);
            break;
        }
    }
    //todo handle the case when there is not free platforms -> queue
}

void cm::CMS::SendTrain(cm::Platform *platform) {
    std::cout << "*** CMS Send train from: " << *platform << std::endl
              << "*********************************************" << std::endl;
    trainLeftStation(platform->trainDepart());
    std::cout << std::endl;
}

void cm::CMS::LoadTrain(cm::Platform *platform) {
    std::cout << "*** CMS loaded train at: " << *platform << std::endl;

    //todo add unload algorithm
    trainFullyLoaded(platform);
}
