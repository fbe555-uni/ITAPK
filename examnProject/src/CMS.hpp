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

namespace cm {

    class CMS {
    public:
        //Signals *************************************************************************
        boost::signals2::signal<void(cm::Platform)> trainArrivedAtPlatform;
        boost::signals2::signal<void(cm::Platform)> trainFullyLoaded;
        boost::signals2::signal<void(cm::Train::Ptr)> trainLeftStation;

        //Slots ***************************************************************************
        struct ReceiveTrain {
            void operator()(cm::Train::Ptr train, cm::Station station) {
                std::cout << " CMS Received train: " << train << std::endl;
            }
        };

        struct sendTrain {
            void operator()(cm::Platform platform) {
                std::cout << "CMS Send train from platform: " << platform << std::endl;
            }
        };

        struct loadTrain {
            void operator()(cm::Platform platform) {
                std::cout << "CMS loaded train at platform: " << platform << std::endl;
            }
        };

        //**********************************************************************************
        void setSimulationController(SimulationController* s) ;

    private:
        SimulationController *sim_;
        std::shared_ptr<cm::Station> station_;
    };
}
#endif //CMS_CMS_H
