#include <iostream>
#include <boost/signals2.hpp>
#include <thread>
#include "trains.hpp"
#include "station.hpp"
#include "CMS.hpp"

//#include "SimulationController.hpp"

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
    /*
    std::vector<cm::Train::Ptr> trainList;
    trainList.push_back(cm::Train::Ptr(new Train1_t("First train")));
    trainList.push_back(cm::Train::Ptr(new Train2_t("Second train")));
    trainList.push_back(cm::Train::Ptr(new Train1_t("Third train")));

    cm::Carriage<100, cm::CARGO_LIST<cm::Timber, cm::Grains, cm::Sheep> > mixedCarriage = cm::Carriage<100, cm::CARGO_LIST<cm::Timber, cm::Grains, cm::Sheep> > ();
    //cm::Carriage<100, cm::CARGO_LIST<cm::Timber, cm::Grains, cm::Sheep, cm::Cows> > illegalCarriage1 = cm::Carriage<100, cm::CARGO_LIST<cm::Timber, cm::Grains, cm::Sheep, cm::Cows> > ();
    //cm::Carriage<100, cm::CARGO_LIST<cm::Oil, cm::Water> > tankerCarriage = cm::Carriage<100, cm::CARGO_LIST<cm::Oil, cm::Water> >();
    //cm::Carriage<100, cm::CARGO_LIST<int, cm::Timber, cm::Grains> > notCargoCarriage = cm::Carriage<100, cm::CARGO_LIST<int, cm::Timber, cm::Grains> > ();
    //cm::Carriage<100, cm::CARGO_LIST<cm::Oil, cm::Water, cm::Coal> > illegalCarriage2 = cm::Carriage<100, cm::CARGO_LIST<cm::Oil, cm::Water, cm::Coal> >();

    */
    std::list<cm::Train::Ptr> trains;
    trains.push_back(cm::Train::Ptr(new Train1_t("Train of the West")));
    trains.push_back(cm::Train::Ptr(new Train1_t("Tøffe")));
    trains.push_back(cm::Train::Ptr(new Train2_t("Eastbound and down")));
    trains.push_back(cm::Train::Ptr(new Train2_t("Thomas")));
    cm::CMS cms("Haste Station", 2);
    cms.StartCMS();
    SimulationController sc(&cms);
    sc.StartSimulation(trains);
    while(true);
    return 0;
}
