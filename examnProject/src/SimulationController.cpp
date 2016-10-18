//
// Created by huxx on 10/18/16.
//

#include "SimulationController.hpp"

SimulationController::SimulationController(ST3000::CMS *cms) {
    cms_ = cms;
    cms_->setSimulationController(this);
    cms_->trainLeftStation.connect(ReceiveTrainAndUnload());
    trainUnloadedAndSend.connect(sendTrain());

}
