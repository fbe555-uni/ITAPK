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
        boost::signals2::signal<void(cm::Platform *)> trainFullyLoaded;
        boost::signals2::signal<void(cm::Train::Ptr)> trainLeftStation;
        //*********************************************************************************

        CMS(std::string, int);

        void Status(){
            station.Status();
        }
        // start thread event handler
        void StartCMS();

        void EventHandler();

        void SetSimulationController(SimulationController*);

        std::string getID() const;

        void ReceiveTrain(cm::Train::Ptr);

        void SendTrain(cm::Platform*);

    private:
        std::queue<boost::variant<int>> eventQueue;//TODO define variant

        void LoadTrain(cm::Platform*);

        std::string ID;
        SimulationController *SimControl;
        cm::Station station;

        void UnQueueTrain();
    };
}
#endif //CMS_CMS_H
