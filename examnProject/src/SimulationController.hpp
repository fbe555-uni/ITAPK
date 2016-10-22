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
    boost::signals2::signal<void(cm::Train::Ptr, cm::Station)> trainArrivedAtStation;
    boost::signals2::signal<void(cm::Train::Ptr)> trainUnloadedAndSend;

    SimulationController(cm::CMS *cms, std::list<cm::Train::Ptr>);

    //Slots *************************************************************
    struct ReceiveTrainAndUnload {
        void operator()(cm::Train::Ptr train) {
            std::cout << " Sim Received train: " << train << std::endl;
        }
    };

    struct sendTrain {
        void operator()(cm::Train::Ptr train) {
            std::cout << "Sim Send train: " << train << std::endl;
        }
    };
    //*******************************************************************


    void startSimulation(std::list<cm::Train> train);

private:
    cm::CMS *cms_;
    std::list<cm::Train::Ptr> _trains;
};


#endif //CMS_SIMULATIONCONTROLLER_H
