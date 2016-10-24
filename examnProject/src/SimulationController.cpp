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
              cond_m(),
              running(false)
{
    cms_->SetSimulationController(this);
    cms_->trainLeftStation.connect([&](cm::Train::Ptr t) {
        ReceiveTrain(t);
    });
    trainUnloaded.connect([&](cm::Train::Ptr t) {
        PushEvent(Event_TrainUnloaded(t));
    });

}
SimulationController::~SimulationController() {
    if(running) StopSimulation();
}

void SimulationController::StartSimulation(std::list<cm::Train::Ptr> &trains) {
    running = true;
    event_sc = std::thread([this] {EventHandler();});
    cms_->StartCMS();
    tp::print("Simulation controller starting.");
    while (!trains.empty()){
        SendTrain(trains.front());
        trains.pop_front();
    }
}

void SimulationController::StopSimulation() {
    cms_->StopCMS();
    tp::print("Stopping simulation controller");
    PushEvent(Event_Shutdown());
    event_sc.join();
}

void SimulationController::PushEvent(SimulationController::Event e){
    std::lock_guard<std::recursive_mutex> lock(cond_m);
    eventQueue.push(e);
    lock.~lock_guard();
    cond.notify_all();
}

void SimulationController::SendTrain(cm::Train::Ptr train) {
    //TODO MAYBE add composer StringStream to all strings
    tp::print("*** Simulation Controller send ", train, " to ", cms_->getID());
    trainArrivedAtStation(train);
}

void SimulationController::ReceiveTrain(cm::Train::Ptr train) {
    tp::print("*** Simulation Controller received : ", train);
    PushEvent(Event_TrainArrived(train));
}

void SimulationController::UnloadTrain(cm::Train::Ptr train) {
    if(! train){
        tp::print("!!Received null train for unloading!!");
        return;
    }
    tp::print("*** Simulation Controller unloading :", train);
    while(!train->isEmpty()){
        train->unload();
    }
    tp::print("*** Simulation Controller unloaded : ", train);
    trainUnloaded(train);
}

void SimulationController::EventHandler() {
    std::unique_lock<std::recursive_mutex> lock(cond_m, std::defer_lock);
    //TODO: add end condition
    while(running){
        //lock.lock();
        while (eventQueue.empty()) {
            wait(lock);
        }
        lock.lock();
        Event e = eventQueue.front();
        eventQueue.pop();
        lock.unlock();

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
void SimulationController::ScHandleEventVisitor::operator()(const Event_Shutdown &e) const {
    _sc->running = false;
}