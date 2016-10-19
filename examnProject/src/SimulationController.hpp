//
// Created by huxx on 10/18/16.
//

#ifndef CMS_SIMULATIONCONTROLLER_H
#define CMS_SIMULATIONCONTROLLER_H

#include "trains.hpp"
#include "CMS.hpp"

namespace cm{class CMS;}

class SimulationController {
public:

    //Signals ***********************************************************
    static boost::signals2::signal<void(cm::Train::Ptr&&, cm::Station*)> trainArrivedAtStation;
    boost::signals2::signal<void(cm::Train::Ptr&&,cm::Station*)> trainUnloadedAndSend;

    SimulationController(cm::CMS* cms, std::list<cm::Train>);

    //Slots *************************************************************
    struct ReceiveTrainAndUnload {
        void operator()(cm::Train::Ptr&& train) {
            std::cout << " Sim Received train: " << *train << std::endl;
        }
    };

    struct SendTrain {
        void operator()(cm::Train::Ptr&& train,cm::Station* station) {
            std::cout << "Sim Send " << *train << " to " << station << std::endl;
            trainArrivedAtStation(train, station);
        }
    };
    //*******************************************************************


    void startSimulation(std::list<cm::Train>,cm::Station*);

private:
    cm::CMS *cms_;
    std::list<cm::Train> _trains;
};


#endif //CMS_SIMULATIONCONTROLLER_H
