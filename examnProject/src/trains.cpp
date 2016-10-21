//
// Created by felix on 10/17/16.
//

#include "trains.hpp"
int cm::Train::num_id = 0;

std::string cm::Train::getID() const {
        return ID;
    }

bool cm::Train::load(cm::Cargo::Ptr) {
    std::cout<< "Loading " << *this << std::endl;
    sleep(10);
}

std::list<cm::Cargo::Ptr> cm::Train::unload() {
    std::list<cm::Cargo::Ptr> cargoList;
    std::cout<< "Unloading " << *this << std::endl;
    sleep(10);
    return cargoList;
}

cm::Train::Train() {
        num_id++;
        ID = "Train #" + std::to_string(num_id);

}

bool cm::Train::canHold(cm::Cargo::Ptr) {
    return false;
}

int cm::Train::getTotalWeight() {
    return 0;
}

int cm::Train::getCapacity() {
    return 0;
}
