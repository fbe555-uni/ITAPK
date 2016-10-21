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
    Train1_t train;

    std::cout << "Can it take 50 coal?: " << std::to_string(train.canHold(std::make_shared<cm::Coal>(50))) << std::endl;
    std::cout << "Can it take 200 grains?: " << std::to_string(train.canHold(std::make_shared<cm::Grains>(200))) << std::endl;
    std::cout << "Can it take 50 cows?: " << std::to_string(train.canHold(std::make_shared<cm::Cows>(50))) << std::endl;

    return 0;
}