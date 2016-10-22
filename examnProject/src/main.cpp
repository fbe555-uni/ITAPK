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

    std::vector<cm::Train::Ptr> trainList;
    trainList.push_back(cm::Train::Ptr(new Train1_t("First train")));
    trainList.push_back(cm::Train::Ptr(new Train2_t("Second train")));
    trainList.push_back(cm::Train::Ptr(new Train1_t("Third train")));

    std::cout << "Can \"" << trainList[0] << "\" take 50kg coal?: " << std::to_string(trainList[0]->canHold(std::make_shared<cm::Coal>(50))) << std::endl;
    std::cout << "Can \"" << trainList[1] << "\" take 200kg grains?: " << std::to_string(trainList[1]->canHold(std::make_shared<cm::Grains>(200))) << std::endl;
    std::cout << "Can \"" << trainList[2] << "\" take 50kg cows?: " << std::to_string(trainList[2]->canHold(std::make_shared<cm::Cows>(50))) << std::endl;

    return 0;
}