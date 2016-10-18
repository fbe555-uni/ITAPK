//
// Created by huxx on 10/18/16.
//

#ifndef CMS_SIMULATIONCONTROLLER_H
#define CMS_SIMULATIONCONTROLLER_H

#include "trains.hpp"
#include "CMS.hpp"

namespace ST3000{class CMS;}

class SimulationController {
public:

    //Signals ***********************************************************
    boost::signals2::signal<void(ST3000::Train,ST3000::Station)> trainArrivedAtStation;
    boost::signals2::signal<void(ST3000::Train)> trainUnloadedAndSend;

    SimulationController(ST3000::CMS* cms, std::list<ST3000::Train>);

    //Slots *************************************************************
    struct ReceiveTrainAndUnload {
        void operator()(ST3000::Train train) {
            std::cout << " Sim Received train: " << train << std::endl;
        }
    };

    struct sendTrain {
        void operator()(ST3000::Train train) {
            std::cout << "Sim Send train: " << train << std::endl;
        }
    };
    //*******************************************************************


    void startSimulation(){
        //send list of trains to the CMS system.

    }

private:
    ST3000::CMS *cms_;
    std::list<ST3000::Train> _trains;
};


#endif //CMS_SIMULATIONCONTROLLER_H
