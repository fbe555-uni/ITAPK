//
// Created by huxx on 10/18/16.
//

#include "SimulationController.hpp"

//TODO fix train pointers in this function and the one below (simulationcontroller)
SimulationController::SimulationController(cm::CMS *cms, std::list<cm::Train> trains) {
    cms_ = cms;
    _trains = trains;
    cms_->setSimulationController(this);
    cms_->trainLeftStation.connect(ReceiveTrainAndUnload());
    trainUnloadedAndSend.connect(SendTrain());


}

void SimulationController::startSimulation(std::list<cm::Train> trains, cm::Station* station) {
    for(auto train:trains){
        trainUnloadedAndSend(&train, station);
    }

}
