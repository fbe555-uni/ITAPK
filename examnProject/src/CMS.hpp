//
// Created by felix on 10/17/16.
//

#ifndef CMS_CMS_H
#define CMS_CMS_H


#include <boost/signals2.hpp>
#include "trains.hpp"
#include "station.hpp"
#include "SimulationController.hpp"

class SimulationController;

namespace ST3000 {

    class CMS {
    public:
        //Signals *************************************************************************
        boost::signals2::signal<void(ST3000::Platform)> trainArrivedAtPlatform;
        boost::signals2::signal<void(ST3000::Platform)> trainFullyLoaded;
        boost::signals2::signal<void(ST3000::Train)> trainLeftStation;

        //Slots ***************************************************************************
        struct ReceiveTrain {
            void operator()(ST3000::Train train, ST3000::Station station) {
                std::cout << " CMS Received train: " << train << std::endl;
            }
        };

        struct sendTrain {
            void operator()(ST3000::Platform platform) {
                std::cout << "CMS Send train from platform: " << platform << std::endl;
            }
        };

        struct loadTrain {
            void operator()(ST3000::Platform platform) {
                std::cout << "CMS loaded train at platform: " << platform << std::endl;
            }
        };

        //**********************************************************************************
        void setSimulationController(SimulationController* s) ;

    private:
        SimulationController *sim_;
        std::shared_ptr<ST3000::Station> station_;
    };
}
#endif //CMS_CMS_H
