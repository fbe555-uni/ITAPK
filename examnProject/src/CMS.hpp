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
    struct Event_TrainAtStation{
        Event_TrainAtStation(Train::Ptr t) : train(t){}
        Train::Ptr train;
    };
    struct Event_TrainAtPlatform{
        Event_TrainAtPlatform(Train::Ptr t) : train(t){}
        Train::Ptr train;
    };
    struct Event_TrainFullyLoaded{
        Event_TrainFullyLoaded(Platform* p) : platform_ptr(p){}
        Platform* platform_ptr;
    };
    struct Event_TrainLeftStation{};

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

        void SetSimulationController(SimulationController *s);

        std::string getID() const;

        void ReceiveTrain(cm::Train::Ptr train);

        void SendTrain(cm::Platform *platform);

        class CmsHandleEventVisitor : boost::static_visitor<>{
        public:
            CmsHandleEventVisitor(CMS* cms);
            void operator()(const Event_TrainAtStation& e) const;
            void operator()(const Event_TrainAtPlatform& e) const;
            void operator()(const Event_TrainFullyLoaded& e) const;
            void operator()(const Event_TrainLeftStation& e) const;
        private:
            CMS* _cms;
        };

    private:
        void LoadTrain(cm::Platform *platform);

        std::string ID;
        SimulationController *SimControl;
        cm::Station station;

        void DequeueTrains();
    };
}
#endif //CMS_CMS_H
