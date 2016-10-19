//
// Created by felix on 10/17/16.
//

#include "CMS.hpp"

void cm::CMS::setSimulationController(SimulationController *s) {
        simulationController = s;

        simulationController->trainArrivedAtStation.connect(ReceiveTrain());
        trainArrivedAtPlatform.connect(LoadTrain());
        trainFullyLoaded.connect(SendTrain());
}

cm::CMS::CMS(cm::Station *s) {
    station = s;
}
