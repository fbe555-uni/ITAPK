//
// Created by felix on 10/17/16.
//

#include "CMS.hpp"

void cm::CMS::SetSimulationController(SimulationController *s) {
    SimControl = s;

    SimControl->trainArrivedAtStation.connect([&](cm::Train::Ptr t) {
        eventQueue.push(Event_TrainAtStation(t));
    });
    trainAtPlatform.connect([&](cm::Platform *p) {
        eventQueue.push(Event_TrainAtPlatform(p));
    });
    trainFullyLoaded.connect([&](cm::Platform *p) {
        eventQueue.push(Event_TrainFullyLoaded(p));
    });
    trainLeftStation.connect([&](cm::Train::Ptr t) {
        eventQueue.push(Event_TrainLeftStation());
    });
}

cm::CMS::CMS(std::string station_name, int num_platforms) : station(station_name, num_platforms), event_visitor(this) {
    ID = station.getName() + " -- Cargo controller";
}

void cm::CMS::Status() const {
    station.Status();
}

std::string cm::CMS::getID() const {
    return ID;
}

void cm::CMS::SendTrainToPlatform(cm::Train::Ptr train) {

    if (station.isFull()) {
        station.getTrainQueue()->push(train);
        std::cout << "Added " << train << " to queue" << std::endl;
        //TODO add conditional to wait for free space
        return;
    }

    //calculate possible load weight for each platform and determine best platform
    Platform best_platform;
    auto platforms = station.getPlatforms();
    int temp_load = 0;
    for (auto &platform:*platforms) {
        auto platform_load = train->calculatePossibleLoad(platform.getCargoList());
        if (platform_load > temp_load) {
            temp_load = platform_load;
            platform = best_platform;
        }
    }
    if (best_platform.trainArrive(train))
        trainAtPlatform(&best_platform);
    std::cout << "*** CMS received train: " << train << " at " << best_platform << std::endl;
    if (temp_load == 0) {
        if (station.isEmpty())
            decommissionedTrains.push_back(train);
        else {
            station.getTrainQueue()->push(train);
            std::cout << "Added " << train << " to queue" << std::endl;
        }
    }
}

void cm::CMS::SendTrain(cm::Platform *platform) {
    std::cout << "*** CMS send " << *platform->getTrain() << " from: " << *platform << std::endl;
    //TODO: vores segfault kommer herfra fordi trainDepart returnerer en tom train::ptr
    trainLeftStation(platform->trainDepart());
    std::cout << std::endl;
}


void cm::CMS::LoadTrain(cm::Platform *platform) {
    std::cout << "*** CMS loading " << *platform->getTrain() << " at: " << *platform << std::endl;
    std::for_each(platform->getCargoList().begin(), platform->getCargoList().end(),
                  [&platform](Cargo::Ptr c) { platform->getTrain()->load(c); });
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

void cm::CMS::EventHandler() {
    boost::apply_visitor(event_visitor, eventQueue.front());
    eventQueue.pop();
}

void cm::CMS::StartCMS() {
    std::thread event_cms;
    event_cms = std::thread([this] { EventHandler(); });
}

bool cm::CMS::HasCargo() {
    return station.HasCargo();
}


int cm::CMS::getNumDecommissionedTrains() {
    return (int) decommissionedTrains.size();
}


cm::CMS::CmsHandleEventVisitor::CmsHandleEventVisitor(cm::CMS *cms) : _cms(cms) {}

void cm::CMS::CmsHandleEventVisitor::operator()(const cm::Event_TrainAtStation &e) const {
    _cms->SendTrainToPlatform(e.train);
}

void cm::CMS::CmsHandleEventVisitor::operator()(const cm::Event_TrainAtPlatform &e) const {
    std::thread([this, e] { _cms->LoadTrain(e.platform); });
}

void cm::CMS::CmsHandleEventVisitor::operator()(const cm::Event_TrainFullyLoaded &e) const {
    _cms->SendTrain(e.platform_ptr);
}

void cm::CMS::CmsHandleEventVisitor::operator()(const cm::Event_TrainLeftStation &e) const {
    _cms->DequeueTrains();
}