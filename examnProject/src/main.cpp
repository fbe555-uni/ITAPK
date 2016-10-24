#define LOAD_SPEED_MULTIPLIER 500

#include <iostream>
#include <boost/signals2.hpp>
#include <thread>
#include "trains.hpp"
#include "station.hpp"
#include "CMS.hpp"

int main() {
    typedef cm::TrainImpl<cm::Locomotive<1000>,
            cm::CARRIAGE_LIST<
                    cm::Carriage<100, cm::CARGO_LIST<cm::Grains> >,
                    cm::Carriage<200, cm::CARGO_LIST<cm::Water, cm::Oil> >,
                    cm::Carriage<300, cm::CARGO_LIST<cm::Sheep, cm::Timber> >,
                    cm::Carriage<400, cm::CARGO_LIST<cm::Timber, cm::Coal> >
            > > Train1_t;
    typedef cm::TrainImpl<cm::Locomotive<1000>,
            cm::CARRIAGE_LIST<
                    cm::Carriage<50, cm::CARGO_LIST<cm::Timber, cm::Cows> >,
                    cm::Carriage<150, cm::CARGO_LIST<cm::Water, cm::Oil, cm::Gasoline> >,
                    cm::Carriage<250, cm::CARGO_LIST<cm::Sheep, cm::Timber> >,
                    cm::Carriage<350, cm::CARGO_LIST<cm::Grains, cm::Pigs> >
            > > Train2_t;

    std::list<cm::Cargo::Ptr> cargo1;
    cargo1.insert(cargo1.begin(), 20, cm::Cargo::Ptr(new cm::Timber(20)));
    cargo1.insert(cargo1.begin(), 30, cm::Cargo::Ptr(new cm::Cows(50)));
    cargo1.insert(cargo1.begin(), 10, cm::Cargo::Ptr(new cm::Sheep(100)));
    cargo1.insert(cargo1.begin(), 200, cm::Cargo::Ptr(new cm::Oil(50)));
    cargo1.insert(cargo1.begin(), 40, cm::Cargo::Ptr(new cm::Oil(100)));
    cargo1.insert(cargo1.begin(), 100, cm::Cargo::Ptr(new cm::Grains(10)));

    std::list<cm::Cargo::Ptr> cargo2;
    cargo2.insert(cargo2.begin(), 60, cm::Cargo::Ptr(new cm::Pigs(20)));
    cargo2.insert(cargo2.begin(), 30, cm::Cargo::Ptr(new cm::Pigs(50)));
    cargo2.insert(cargo2.begin(), 100, cm::Cargo::Ptr(new cm::Gasoline(60)));
    cargo2.insert(cargo2.begin(), 10, cm::Cargo::Ptr(new cm::Water(20)));
    cargo2.insert(cargo2.begin(), 100, cm::Cargo::Ptr(new cm::Coal(50)));
    cargo2.insert(cargo2.begin(), 40, cm::Cargo::Ptr(new cm::Grains(100)));

    std::list<cm::Train::Ptr> trains;
    trains.push_back(cm::Train::Ptr(new Train1_t("Train of the West")));
    trains.push_back(cm::Train::Ptr(new Train1_t("Tøffe")));
    //trains.push_back(cm::Train::Ptr(new Train2_t("Eastbound and down")));
    //trains.push_back(cm::Train::Ptr(new Train2_t("Thomas")));
    int num_trains = trains.size();

    cm::CMS cms("Haste Station", 2);
    cms.addCargo(cargo1, 0);
    cms.addCargo(cargo2, 1);
    SimulationController sc(&cms);
    sc.StartSimulation(trains);
    while(cms.getNumDecommissionedTrains() < num_trains){
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    auto dur = sc.StopSimulation();
    tp::print("**********************************************");
    tp::print("*  Simulation ended, after: ", dur.count(), " seconds (", dur.count()*LOAD_SPEED_MULTIPLIER, " realtime seconds)");
    tp::print("*  Station has been emptied: ", !cms.HasCargo());
    tp::print("*  The status at the end was as follows:");
    cms.Status();

    //****************** RERUN***************************************
    tp::print("Will rerun simulation with sufficient trains in 20 seconds: ");
    std::this_thread::sleep_for(std::chrono::seconds(20));

    std::list<cm::Train::Ptr> trains2;
    trains2.push_back(cm::Train::Ptr(new Train1_t("Train of the West")));
    trains2.push_back(cm::Train::Ptr(new Train1_t("Tøffe")));
    trains2.push_back(cm::Train::Ptr(new Train2_t("Eastbound and down")));
    trains2.push_back(cm::Train::Ptr(new Train2_t("Thomas")));
    num_trains = trains2.size();

    cargo1.insert(cargo1.begin(), 20, cm::Cargo::Ptr(new cm::Timber(20)));
    cargo1.insert(cargo1.begin(), 30, cm::Cargo::Ptr(new cm::Cows(50)));
    cargo1.insert(cargo1.begin(), 10, cm::Cargo::Ptr(new cm::Sheep(100)));
    cargo1.insert(cargo1.begin(), 200, cm::Cargo::Ptr(new cm::Oil(50)));
    cargo1.insert(cargo1.begin(), 40, cm::Cargo::Ptr(new cm::Oil(100)));
    cargo1.insert(cargo1.begin(), 100, cm::Cargo::Ptr(new cm::Grains(10)));

    cargo2.insert(cargo2.begin(), 60, cm::Cargo::Ptr(new cm::Pigs(20)));
    cargo2.insert(cargo2.begin(), 30, cm::Cargo::Ptr(new cm::Pigs(50)));
    cargo2.insert(cargo2.begin(), 100, cm::Cargo::Ptr(new cm::Gasoline(60)));
    cargo2.insert(cargo2.begin(), 10, cm::Cargo::Ptr(new cm::Water(20)));
    cargo2.insert(cargo2.begin(), 100, cm::Cargo::Ptr(new cm::Coal(50)));
    cargo2.insert(cargo2.begin(), 40, cm::Cargo::Ptr(new cm::Grains(100)));

    cm::CMS cms2("Haste Station", 2);
    cms2.addCargo(cargo1, 0);
    cms2.addCargo(cargo2, 1);

    SimulationController sc2(&cms2);
    sc2.StartSimulation(trains2);
    while(cms2.getNumDecommissionedTrains() < num_trains){
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    dur = sc2.StopSimulation();
    tp::print("**********************************************");
    tp::print("*  Simulation ended, after: ", dur.count(), " seconds (", dur.count()*LOAD_SPEED_MULTIPLIER, " realtime seconds)");
    tp::print("*  Station has been emptied: ", !cms2.HasCargo());
    tp::print("*  The status at the end was as follows:");
    cms2.Status();
    return 0;
}
