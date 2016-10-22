//
// Created by felix on 10/17/16.
//

#include "CMS.hpp"

void cm::CMS::SetSimulationController(SimulationController *s) {
    SimControl = s;

    SimControl->trainArrivedAtStation.connect([&](cm::Train::Ptr t) {
        ReceiveTrain(t);
    });

    trainFullyLoaded.connect([&](cm::Platform *p) {
        SendTrain(p);
    });
    trainLeftStation.connect([&](cm::Train::Ptr) {
        DequeueTrains();
    });
}

cm::CMS::CMS(std::string station_name, int num_platforms) : station(station_name, num_platforms) {
    ID = *station.getName() + " -- Cargo controller";
}

std::string cm::CMS::getID() const {
    return ID;
}

void cm::CMS::ReceiveTrain(cm::Train::Ptr train) {
    if (station.isFull()) {
        station.getTrainQueue()->push(train);
        std::cout << "Added " << *train << " to queue" << std::endl;
        return;
    }
    std::cout << "*** CMS received train: " << *train << std::endl;
    auto platforms = station.getPlatforms();
    for (auto &platform:*platforms) {
        if (platform.trainArrive(train))
            LoadTrain(&platform);
    }
}


void cm::CMS::SendTrain(cm::Platform *platform) {
    std::cout << "*** CMS send " << *platform->getTrain() << " from: " << *platform << std::endl;
    trainLeftStation(platform->trainDepart());
    std::cout << std::endl;
}

void cm::CMS::LoadTrain(cm::Platform *platform) {
    std::cout << "*** CMS loading " << *platform->getTrain() << " at: " << *platform << std::endl;
    //    platform->getTrain()->load(platform->getCargoList().front());
    sleep((unsigned int) (rand() % 20));
    std::cout << "*** CMS loaded " << *platform->getTrain() << " at: " << *platform << std::endl;
    trainFullyLoaded(platform);
}

void cm::CMS::DequeueTrains() {
    for (auto &platform:*station.getPlatforms()) {
        auto train = station.getTrainQueue()->front();
        station.getTrainQueue()->pop();
        if (platform.trainArrive(train)) {
            LoadTrain(&platform);
            std::cout << "Removed " << *train << " from queue" << std::endl;
        }
    }
}

cm::CMS::CmsHandleEventVisitor::CmsHandleEventVisitor(cm::CMS* cms): _cms(cms){}

void cm::CMS::CmsHandleEventVisitor::operator()(const cm::Event_TrainAtStation& e) const {
    _cms->ReceiveTrain(e.train);
}

void cm::CMS::CmsHandleEventVisitor::operator()(const cm::Event_TrainAtPlatform& e) const {
    //start loading thread;
}

void cm::CMS::CmsHandleEventVisitor::operator()(const cm::Event_TrainFullyLoaded& e) const {
    _cms->SendTrain(e.platform_ptr);
}

void cm::CMS::CmsHandleEventVisitor::operator()(const cm::Event_TrainLeftStation& e) const {
    _cms->DequeueTrains();
}