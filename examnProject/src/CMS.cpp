//
// Created by felix on 10/17/16.
//

#include "CMS.hpp"

void cm::CMS::setSimulationController(SimulationController *s) {
    sim_ = s;

    sim_->trainArrivedAtStation.connect(ReceiveTrain());

    trainArrivedAtPlatform.connect(loadTrain());

    trainFullyLoaded.connect(sendTrain());


}
