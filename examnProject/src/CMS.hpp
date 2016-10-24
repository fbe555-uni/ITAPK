//
// Created by felix on 10/17/16.
//

#ifndef CMS_CMS_H
#define CMS_CMS_H


#include <boost/signals2.hpp>
#include <condition_variable>
#include "trains.hpp"
#include "station.hpp"
#include "SimulationController.hpp"
#include "ThreadSafeCout.hpp"

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
    struct Event_Shutdown{};

    class CMS {
    public:
        typedef boost::variant<Event_TrainAtStation, Event_TrainAtPlatform, Event_TrainFullyLoaded, Event_TrainLeftStation, Event_Shutdown> Event;
        //Signals *************************************************************************
        boost::signals2::signal<void(cm::Platform*)> trainAtPlatform;
        boost::signals2::signal<void(cm::Platform*)> trainFullyLoaded;
        boost::signals2::signal<void(cm::Train::Ptr)> trainLeftStation;
        //*********************************************************************************

        //constructor:
        //TODO: rule of 5 this mother F***er
        CMS(std::string, int);
        ~CMS();

        //bind to a simulation controller:
        void SetSimulationController(SimulationController*);

        // start thread event handler:
        void StartCMS();
        void StopCMS();

        //state and status functions:

        std::string getID() const;

        bool HasCargo();

        void PushEvent(Event e);

        int getNumDecommissionedTrains();

        void addCargo(std::list<Cargo::Ptr>& cargo, int platformNumber = -1);

    private:
        volatile bool running;
        std::string ID;
        SimulationController *simControl;
        cm::Station station;
        std::list<Train::Ptr> decommissionedTrains;



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
            void operator()(const Event_Shutdown& e) const;
        private:
            CMS* _cms;
        };

        std::queue<Event> eventQueue;
        CmsHandleEventVisitor event_visitor;

        std::thread event_cms;
        std::condition_variable cond;
        std::recursive_mutex cond_m;

    };
}
#endif //CMS_CMS_H
