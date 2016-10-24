//
// Created by huxx on 10/18/16.
//

#ifndef CMS_SIMULATIONCONTROLLER_H
#define CMS_SIMULATIONCONTROLLER_H

#include "trains.hpp"
#include "CMS.hpp"

namespace cm { class CMS; }

class Event_TrainArrived{
public:
    Event_TrainArrived(cm::Train::Ptr t): train(t){}
    cm::Train::Ptr train;
};
class Event_TrainUnloaded{
public:
    Event_TrainUnloaded(cm::Train::Ptr t): train(t){}
    cm::Train::Ptr train;
};
struct Event_Shutdown{};

class SimulationController {
public:
    typedef boost::variant<Event_TrainArrived, Event_TrainUnloaded, Event_Shutdown> Event;
    //Signals ***********************************************************
    boost::signals2::signal<void(cm::Train::Ptr)> trainArrivedAtStation;
    boost::signals2::signal<void(cm::Train::Ptr)> trainUnloaded;
    //*******************************************************************

    //start event handler thread
    SimulationController(cm::CMS *cms);
    ~SimulationController();

    void StartSimulation(std::list<cm::Train::Ptr> &);
    void StopSimulation();

    void PushEvent(Event e);
private:
    volatile bool running;
    cm::CMS *cms_;

    void EventHandler();
    void ReceiveTrain(cm::Train::Ptr);
    void UnloadTrain(cm::Train::Ptr);
    void SendTrain(cm::Train::Ptr);

    class ScHandleEventVisitor : public boost::static_visitor<>{
    public:
        ScHandleEventVisitor(SimulationController* sc);
        void operator()(const Event_TrainArrived& e) const;
        void operator()(const Event_TrainUnloaded& e) const;
        void operator()(const Event_Shutdown& e) const;
    private:
        SimulationController* _sc;
    };


    std::queue<Event> eventQueue;
    ScHandleEventVisitor event_visitor;
    std::thread event_sc;
    std::condition_variable cond;
    std::recursive_mutex cond_m;
};


#endif //CMS_SIMULATIONCONTROLLER_H
