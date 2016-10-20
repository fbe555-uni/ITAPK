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

//TODO add rule of five
    class CMS {

    public:
        //Signals *************************************************************************
        boost::signals2::signal<void(cm::Platform *)> trainFullyLoaded;
        boost::signals2::signal<void(cm::Train::Ptr)> trainLeftStation;
        //*********************************************************************************

        CMS(std::string, int);

        void setSimulationController(SimulationController *s);

        std::string getID() const;

        void ReceiveTrain(cm::Train::Ptr train);

        void SendTrain(cm::Platform *platform);

    private:
        void LoadTrain(cm::Platform *platform);

        std::string ID;
        SimulationController *SimControl;
        cm::Station station;
    };
}
#endif //CMS_CMS_H