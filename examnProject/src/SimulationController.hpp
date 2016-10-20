//
// Created by huxx on 10/18/16.
//

#ifndef CMS_SIMULATIONCONTROLLER_H
#define CMS_SIMULATIONCONTROLLER_H

#include "trains.hpp"
#include "CMS.hpp"

namespace cm { class CMS; }

class SimulationController {
public:

    //Signals ***********************************************************
    boost::signals2::signal<void(cm::Train::Ptr)> trainArrivedAtStation;
    boost::signals2::signal<void(cm::Train::Ptr)> trainUnloaded;
    //*******************************************************************

    SimulationController(cm::CMS *cms);

    void startSimulation(std::list<cm::Train::Ptr> &);

    void ReceiveTrain(cm::Train::Ptr train);

    void SendTrain(cm::Train::Ptr train);

private:
    void UnloadTrain(cm::Train::Ptr train);

    cm::CMS *cms_;
};


#endif //CMS_SIMULATIONCONTROLLER_H
