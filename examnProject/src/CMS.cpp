//
// Created by felix on 10/17/16.
//

#include "CMS.hpp"

void cm::CMS::SetSimulationController(SimulationController *s) {
    SimControl = s;

    SimControl->trainArrivedAtStation.connect([&](cm::Train::Ptr t) {
        pushEvent(Event_TrainAtStation(t));
    });
    trainAtPlatform.connect([&](cm::Platform* p){
        pushEvent(Event_TrainAtPlatform(p));
    });
    trainFullyLoaded.connect([&](cm::Platform *p) {
        pushEvent(Event_TrainFullyLoaded(p));
    });
    trainLeftStation.connect([&](cm::Train::Ptr t) {
        pushEvent(Event_TrainLeftStation());
    });
}

cm::CMS::CMS(std::string station_name, int num_platforms)
            : station(station_name, num_platforms),
              event_visitor(this),
              cond(),
              cond_m()
{
    ID = station.getName() + " -- Cargo controller";
}

cm::CMS::~CMS(){
    event_cms.join();
}

void cm::CMS::Status() const {
    station.Status();
}

std::string cm::CMS::getID() const {
    return ID;
}


void cm::CMS::pushEvent(cm::CMS::Event e){
    //std::cout << "ready to lock for pushEvent" << std::endl;
    std::lock_guard<std::recursive_mutex> lock(cond_m);
    eventQueue.push(e);
    lock.~lock_guard();
    cond.notify_all();
}

void cm::CMS::SendTrainToPlatform(cm::Train::Ptr train){
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
    if (temp_load == 0) {
        if (station.isEmpty()){
            decommissionedTrains.push_back(train);
            std::cout << "Decomissioned train: " << train;
        }else {
            station.getTrainQueue()->push(train);
            std::cout << "Added " << train << " to queue" << std::endl;
        }
    }else if (best_platform.trainArrive(train)) {
        trainAtPlatform(&best_platform);
        std::cout << "*** CMS received train: " << train << " at " << best_platform << std::endl;
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
    std::unique_lock<std::recursive_mutex> lock(cond_m, std::defer_lock);
    //TODO: add end condition
    while(true){
        //lock.lock();
        while (eventQueue.empty()) {
            wait(lock);
        }
        Event e = eventQueue.front();
        eventQueue.pop();
        lock.unlock();
        boost::apply_visitor(event_visitor, e);
    }
}

void cm::CMS::StartCMS() {
    event_cms = std::thread([this] { EventHandler(); });
}

void cm::CMS::StopCMS() {
    event_cms.join();
}

bool cm::CMS::HasCargo() {
    return station.HasCargo();
}


int cm::CMS::getNumDecommissionedTrains() {
    return (int) decommissionedTrains.size();
}


cm::CMS::CmsHandleEventVisitor::CmsHandleEventVisitor(cm::CMS* cms): _cms(cms){}

void cm::CMS::CmsHandleEventVisitor::operator()(const cm::Event_TrainAtStation &e) const {
    _cms->SendTrainToPlatform(e.train);
}

void cm::CMS::CmsHandleEventVisitor::operator()(const cm::Event_TrainAtPlatform& e) const {
    std::thread t([this, e]{_cms->LoadTrain(e.platform);});
    t.detach();
}

void cm::CMS::CmsHandleEventVisitor::operator()(const cm::Event_TrainFullyLoaded &e) const {
    _cms->SendTrain(e.platform_ptr);
}

void cm::CMS::CmsHandleEventVisitor::operator()(const cm::Event_TrainLeftStation &e) const {
    _cms->DequeueTrains();
}