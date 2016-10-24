//
// Created by felix on 10/17/16.
//

#include "CMS.hpp"

void cm::CMS::SetSimulationController(SimulationController *s) {
    simControl = s;

    simControl->trainArrivedAtStation.connect([&](cm::Train::Ptr t) {
        PushEvent(Event_TrainAtStation(t));
    });
    trainAtPlatform.connect([&](cm::Platform *p) {
        PushEvent(Event_TrainAtPlatform(p));
    });
    trainFullyLoaded.connect([&](cm::Platform *p) {
        PushEvent(Event_TrainFullyLoaded(p));
    });
    trainLeftStation.connect([&](cm::Train::Ptr t) {
        PushEvent(Event_TrainLeftStation());
    });
}

cm::CMS::CMS(std::string station_name, int num_platforms)
        : station(station_name, num_platforms),
          event_visitor(this),
          cond(),
          cond_m(),
          running(false) {
    ID = station.getName() + " -- Cargo controller";
}

cm::CMS::~CMS() {
    if(running) StopCMS();
}

void cm::CMS::addCargo(std::list<Cargo::Ptr> &cargo, int platformNumber) {
    int i = 0;
    //tp::print(cargo.front());
    for (auto &p: *station.getPlatforms()) {
        if (platformNumber < 0 || i++ == platformNumber) p.addCargo(cargo);
    }
}

std::string cm::CMS::getID() const {
    return ID;
}


void cm::CMS::PushEvent(cm::CMS::Event e) {
    std::lock_guard<std::recursive_mutex> lock(cond_m);
    eventQueue.push(e);
    lock.~lock_guard();
    cond.notify_all();
}

void cm::CMS::SendTrainToPlatform(cm::Train::Ptr train) {
    if (station.isFull()) {
        station.getTrainQueue()->push(train);
        tp::print("Added ", train, " to queue");
        //TODO add conditional to wait for free space
        return;
    }

    //calculate possible load weight for each platform and determine best platform
    Platform *best_platform = NULL;
    std::list<Platform> *platforms = station.getPlatforms();
    int temp_load = 0;
    for (auto &platform: *platforms) {
        if (!platform.isFree()) continue;
        //tp::print(platform.getCargoList()->front());
        auto platform_load = train->calculatePossibleLoad(platform.getCargoList());
        if (platform_load > temp_load) {
            temp_load = platform_load;
            best_platform = &platform;
        }
    }
    if (temp_load == 0) {
        if (station.isEmpty()) {
            decommissionedTrains.push_back(train);
            tp::print("Decomissioned train: ", train);
        } else {
            station.getTrainQueue()->push(train);
            tp::print("Added ", train, " to queue");
        }
    } else if (best_platform->trainArrive(train)) {
        trainAtPlatform(best_platform);
        tp::print("*** CMS received train: ", train, " at ", best_platform);
    } else {
        station.getTrainQueue()->push(train);
        tp::print("Added ", train, " to queue !! unforseen !!");
    }
}

void cm::CMS::SendTrain(cm::Platform *platform) {
    tp::print("*** CMS send ", platform->getTrain(), " from: ", platform);
    trainLeftStation(platform->trainDepart());

}


void cm::CMS::LoadTrain(cm::Platform *platform) {
    tp::print("*** CMS loading ", platform->getTrain(), " at: ", platform);
    platform->getCargoList()->erase(
            std::remove_if(platform->getCargoList()->begin(),
                           platform->getCargoList()->end(),
                           [platform](cm::Cargo::Ptr &c) { return platform->getTrain()->load(c); }),
            platform->getCargoList()->end());

     tp::print("*** CMS loaded ", platform->getTrain(), " at: ", platform);

    trainFullyLoaded(platform);
}

void cm::CMS::DequeueTrains() {
    //TODO: implement a more efficient dequeue system
    tp::print("*** Dequeueing all trains");
    while (!station.getTrainQueue()->empty()) {
        PushEvent(Event_TrainAtStation(station.getTrainQueue()->front()));
        station.getTrainQueue()->pop();
    }
}

void cm::CMS::EventHandler() {
    std::unique_lock<std::recursive_mutex> lock(cond_m, std::defer_lock);
    //TODO: add end condition
    while (running) {
        //lock.lock();
        while (eventQueue.empty()) {
            wait(lock);
        }
        lock.lock();
        Event e = eventQueue.front();
        //tp::print("handling event\n");
        eventQueue.pop();
        lock.unlock();
        boost::apply_visitor(event_visitor, e);
    }
}

void cm::CMS::StartCMS() {
    tp::print("Starting CMS");
    running = true;
    event_cms = std::thread([this] { EventHandler(); });
}

void cm::CMS::StopCMS() {
    tp::print("Stopping CMS");
    PushEvent(Event_Shutdown());
    event_cms.join();
}

bool cm::CMS::HasCargo() {
    return station.hasCargo();
}


int cm::CMS::getNumDecommissionedTrains() {
    return (int) decommissionedTrains.size();
}


cm::CMS::CmsHandleEventVisitor::CmsHandleEventVisitor(cm::CMS *cms) : _cms(cms) {}

void cm::CMS::CmsHandleEventVisitor::operator()(const cm::Event_TrainAtStation &e) const {
    _cms->SendTrainToPlatform(e.train);
}

void cm::CMS::CmsHandleEventVisitor::operator()(const cm::Event_TrainAtPlatform &e) const {
    std::thread t([this, e] { _cms->LoadTrain(e.platform); });
    t.detach();
}

void cm::CMS::CmsHandleEventVisitor::operator()(const cm::Event_TrainFullyLoaded &e) const {
    _cms->SendTrain(e.platform_ptr);
}

void cm::CMS::CmsHandleEventVisitor::operator()(const cm::Event_TrainLeftStation &e) const {
    _cms->DequeueTrains();
}

void cm::CMS::CmsHandleEventVisitor::operator()(const Event_Shutdown& e) const{
    _cms->running = false;
}