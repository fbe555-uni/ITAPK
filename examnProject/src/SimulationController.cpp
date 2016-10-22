//
// Created by huxx on 10/18/16.
//

#include <thread>
#include "SimulationController.hpp"

//TODO fix train pointers in this function and the one below (simulationcontroller)
SimulationController::SimulationController(cm::CMS *cms) : cms_(cms) {
    cms_->SetSimulationController(this);
    cms_->trainLeftStation.connect([&](cm::Train::Ptr t) {
        ReceiveTrain(t);
    });
    trainUnloaded.connect([&](cm::Train::Ptr t) {
        SendTrain(t);
    });
}

void SimulationController::StartSimulation(std::list<cm::Train::Ptr> &trains) {
    std::thread event_sc;
    event_sc = std::thread([this] {EventHandler();});

    while (trains.size()!=0){
        SendTrain(trains.front());
        trains.pop_front();
    }
    for (;;);
}

void SimulationController::SendTrain(cm::Train::Ptr train) {
    //TODO MAYBE add composer StringStream to all strings
    std::cout << "*** Simulation Controller send " << train << " to " << cms_->getID() << std::endl;
    trainArrivedAtStation(train);
}

void SimulationController::ReceiveTrain(cm::Train::Ptr train) {
    std::cout << "*** Simulation Controller received : " << train << std::endl;
    UnloadTrain(train);
}

void SimulationController::UnloadTrain(cm::Train::Ptr train) {
    std::cout << "*** Simulation Controller unloading :" << train << std::endl;
    train->unload();
    std::cout << "*** Simulation Controller unloaded : " << train << std::endl;

    trainUnloaded(train);
}

void SimulationController::EventHandler() {
    boost::apply_visitor(eventQueue.front());
    eventQueue.pop();
}
