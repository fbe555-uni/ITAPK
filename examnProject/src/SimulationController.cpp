//
// Created by huxx on 10/18/16.
//

#include "SimulationController.hpp"

SimulationController::SimulationController(cm::CMS *cms, std::list<cm::Train> trains) {
    cms_ = cms;
    _trains = trains;
    cms_->setSimulationController(this);
    cms_->trainLeftStation.connect(ReceiveTrainAndUnload());
    trainUnloadedAndSend.connect(sendTrain());

}

void SimulationController::startSimulation(std::list<cm::Train> train) {

}
