//
// Created by huxx on 10/18/16.
//

#include <thread>
#include "SimulationController.hpp"

//TODO fix train pointers in this function and the one below (simulationcontroller)
SimulationController::SimulationController(cm::CMS *cms) : cms_(cms), event_visitor(this) {
    cms_->SetSimulationController(this);
    cms_->trainLeftStation.connect([&](cm::Train::Ptr t) {
        ReceiveTrain(t);
    });
    trainUnloaded.connect([&](cm::Train::Ptr t) {
        eventQueue.push(Event_TrainUnloaded(t));
    });
}

void SimulationController::StartSimulation(std::list<cm::Train::Ptr> &trains) {
    std::thread event_sc;
    event_sc = std::thread([this] {EventHandler();});

    while (!trains.empty()){
        SendTrain(trains.front());
        trains.pop_front();
    }

    //TODO: detect end of simulation
    for (;;);
}

void SimulationController::SendTrain(cm::Train::Ptr train) {
    //TODO MAYBE add composer StringStream to all strings
    std::cout << "*** Simulation Controller send " << train << " to " << cms_->getID() << std::endl;
    trainArrivedAtStation(train);
}

void SimulationController::ReceiveTrain(cm::Train::Ptr train) {
    std::cout << "*** Simulation Controller received : " << train << std::endl;
    eventQueue.push(Event_TrainArrived(train));
}

void SimulationController::UnloadTrain(cm::Train::Ptr train) {
    if(! train){
        std::cout << "!!Received null train for unloading!!";
        return;
    }
    std::cout << "*** Simulation Controller unloading :" << train << std::endl;
    while(!train->isEmpty()){
        train->unload();
    }
    std::cout << "*** Simulation Controller unloaded : " << train << std::endl;
    trainUnloaded(train);
}

void SimulationController::EventHandler() {
    boost::apply_visitor(event_visitor, eventQueue.front());
    eventQueue.pop();
}

SimulationController::ScHandleEventVisitor::ScHandleEventVisitor(SimulationController* sc): _sc(sc){}
void SimulationController::ScHandleEventVisitor::operator()(const Event_TrainArrived& e) const{
    //start unloading train in a new thread, signaling train unloaded when done.
    std::thread([this, e]{_sc->UnloadTrain(e.train);});
}
void SimulationController::ScHandleEventVisitor::operator()(const Event_TrainUnloaded& e) const{
    _sc->SendTrain(e.train);
}