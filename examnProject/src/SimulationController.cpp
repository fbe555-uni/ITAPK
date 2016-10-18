//
// Created by huxx on 10/18/16.
//

#include "SimulationController.hpp"

SimulationController::SimulationController(ST3000::CMS *cms, std::list<ST3000::Train> trains) {
    cms_ = cms;
    _trains = trains;
    cms_->setSimulationController(this);
    cms_->trainLeftStation.connect(ReceiveTrainAndUnload());
    trainUnloadedAndSend.connect(sendTrain());

}
