//
// Created by huxx on 10/18/16.
//

#include <thread>
#include "SimulationController.hpp"

//TODO fix train pointers in this function and the one below (simulationcontroller)
SimulationController::SimulationController(cm::CMS *cms)
            : cms_(cms),
              event_visitor(this),
              cond(),
              cond_m()
{
    cms_->SetSimulationController(this);
    cms_->trainLeftStation.connect([&](cm::Train::Ptr t) {
        ReceiveTrain(t);
    });
    trainUnloaded.connect([&](cm::Train::Ptr t) {
        pushEvent(Event_TrainUnloaded(t));
    });
}
SimulationController::~SimulationController() {
    event_sc.join();
}

void SimulationController::StartSimulation(std::list<cm::Train::Ptr> &trains) {
    event_sc = std::thread([this] {EventHandler();});
    std::cout << "Simulation controller starting." << std::endl;
    while (!trains.empty()){
        SendTrain(trains.front());
        trains.pop_front();
    }
}

void SimulationController::pushEvent(SimulationController::Event e){
    std::lock_guard<std::recursive_mutex> lock(cond_m);
    eventQueue.push(e);
    lock.~lock_guard();
    cond.notify_all();
}

void SimulationController::SendTrain(cm::Train::Ptr train) {
    //TODO MAYBE add composer StringStream to all strings
    std::cout << "*** Simulation Controller send " << train << " to " << cms_->getID() << std::endl;
    trainArrivedAtStation(train);
}

void SimulationController::ReceiveTrain(cm::Train::Ptr train) {
    std::cout << "*** Simulation Controller received : " << train << std::endl;
    pushEvent(Event_TrainArrived(train));
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

        std::cout << "Handling event in sc" << std::endl;
        boost::apply_visitor(event_visitor, e);
    }
}

SimulationController::ScHandleEventVisitor::ScHandleEventVisitor(SimulationController* sc): _sc(sc){}
void SimulationController::ScHandleEventVisitor::operator()(const Event_TrainArrived& e) const{
    //start unloading train in a new thread, signaling train unloaded when done.
    std::thread t([this, e]{_sc->UnloadTrain(e.train);});
    t.detach();
}
void SimulationController::ScHandleEventVisitor::operator()(const Event_TrainUnloaded& e) const{
    _sc->SendTrain(e.train);
}