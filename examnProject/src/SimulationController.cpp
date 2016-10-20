//
// Created by huxx on 10/18/16.
//

#include "SimulationController.hpp"

//TODO fix train pointers in this function and the one below (simulationcontroller)
SimulationController::SimulationController(cm::CMS *cms) : cms_(cms) {
    cms_->setSimulationController(this);
    cms_->trainLeftStation.connect([&](cm::Train::Ptr t) {
        ReceiveTrain(t);
    });
    trainUnloaded.connect([&](cm::Train::Ptr t){
        SendTrain(t);
    });
}

void SimulationController::startSimulation(std::list<cm::Train::Ptr> &trains) {
    while (!trains.empty()) {
        SendTrain(*trains.begin());
        trains.pop_front();
    }
}

void SimulationController::SendTrain(cm::Train::Ptr train) {
    std::cout << "*** Simulation Controller send " << *train << " to " << cms_->getID() << std::endl
              << "*********************************************" << std::endl;
    trainArrivedAtStation(train);
}

void SimulationController::ReceiveTrain(cm::Train::Ptr train) {
    std::cout <<std::endl << "*********************************************" << std::endl
              << "*** Simulation Controller received train: " << *train << std::endl;
    UnloadTrain(train);
}

void SimulationController::UnloadTrain(cm::Train::Ptr train) {
    std::cout << "*** Simulation Controller unloaded train: " << *train << std::endl;
    trainUnloaded(train);
    //todo add unload algorithm

}
