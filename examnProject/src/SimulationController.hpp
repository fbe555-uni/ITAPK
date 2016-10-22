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

    //start event handler thread
    SimulationController(cm::CMS *cms);

    void StartSimulation(std::list<cm::Train::Ptr> &);

    void EventHandler();

    void ReceiveTrain(cm::Train::Ptr);

    void SendTrain(cm::Train::Ptr);

private:
    std::queue<boost::variant<int>> eventQueue;//TODO define variant
    void UnloadTrain(cm::Train::Ptr);

    cm::CMS *cms_;
};


#endif //CMS_SIMULATIONCONTROLLER_H
