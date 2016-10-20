#include <iostream>
#include <boost/signals2.hpp>
#include <thread>
#include "trains.hpp"
#include "station.hpp"
#include "CMS.hpp"
//#include "SimulationController.hpp"

int main() {

    cm::Carriage<100, cm::CARGO_LIST<cm::Timber, cm::Grains, cm::Sheep> > mixedCarriage = cm::Carriage<100, cm::CARGO_LIST<cm::Timber, cm::Grains, cm::Sheep> > ();
    //cm::Carriage<100, cm::CARGO_LIST<cm::Timber, cm::Grains, cm::Sheep, cm::Cows> > illegalCarriage1 = cm::Carriage<100, cm::CARGO_LIST<cm::Timber, cm::Grains, cm::Sheep, cm::Cows> > ();
    //cm::Carriage<100, cm::CARGO_LIST<cm::Oil, cm::Water> > tankerCarriage = cm::Carriage<100, cm::CARGO_LIST<cm::Oil, cm::Water> >();
    //cm::Carriage<100, cm::CARGO_LIST<int, cm::Timber, cm::Grains> > notCargoCarriage = cm::Carriage<100, cm::CARGO_LIST<int, cm::Timber, cm::Grains> > ();
    //cm::Carriage<100, cm::CARGO_LIST<cm::Oil, cm::Water, cm::Coal> > illegalCarriage2 = cm::Carriage<100, cm::CARGO_LIST<cm::Oil, cm::Water, cm::Coal> >();
    return 0;
}