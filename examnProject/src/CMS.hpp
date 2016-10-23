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
        Event_TrainAtPlatform(Platform* p) : platform(p){}
        Platform* platform;
    };
    struct Event_TrainFullyLoaded{
        Event_TrainFullyLoaded(Platform* p) : platform_ptr(p){}
        Platform* platform_ptr;
    };
    struct Event_TrainLeftStation{};

    class CMS {
    public:
        typedef boost::variant<Event_TrainAtStation, Event_TrainAtPlatform, Event_TrainFullyLoaded, Event_TrainLeftStation> Event;
        //Signals *************************************************************************
        boost::signals2::signal<void(cm::Platform*)> trainAtPlatform;
        boost::signals2::signal<void(cm::Platform*)> trainFullyLoaded;
        boost::signals2::signal<void(cm::Train::Ptr)> trainLeftStation;
        //*********************************************************************************

        //constructor:
        CMS(std::string, int);

        //bind to a simulation controller:
        void SetSimulationController(SimulationController*);

        // start thread event handler:
        void StartCMS();

        //state and status functions:
        void Status() const;
        std::string getID() const;

        //receive a train
        void ReceiveTrain(cm::Train::Ptr);

    private:
        std::string ID;
        SimulationController *SimControl;
        cm::Station station;

        void EventHandler();
        void SendTrainToPlatform(Train::Ptr train);
        void DequeueTrains();
        void LoadTrain(cm::Platform*);
        void SendTrain(cm::Platform*);

        class CmsHandleEventVisitor : public boost::static_visitor<>{
        public:
            CmsHandleEventVisitor(CMS* cms);
            void operator()(const Event_TrainAtStation& e) const;
            void operator()(const Event_TrainAtPlatform& e) const;
            void operator()(const Event_TrainFullyLoaded& e) const;
            void operator()(const Event_TrainLeftStation& e) const;
        private:
            CMS* _cms;
        };

        std::queue<Event> eventQueue;
        CmsHandleEventVisitor event_visitor;
    };
}
#endif //CMS_CMS_H
