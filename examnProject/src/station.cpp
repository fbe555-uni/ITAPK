//
// Created by felix on 10/17/16.
//


#include "station.hpp"

void cm::Station::Status() {
    int i = 0;
    for (auto item:_platforms) {
        std::cout << "Status from " << item << ":" << std::endl;
        item.Status();
    }
}

cm::Station::Station(std::string n) {
    _name = n;
}

std::list<cm::Platform> *cm::Station::getPlatforms() const {
    return &_platforms;
}


void cm::Platform::Status() {
    std::cout << "Cargo on platform: " << std::endl;
    for (auto item:Platform::_cargo) {
        //TODO this reference i do not understand; at item
        std::cout << &item << std::endl;
    }
    std::cout << "Train on platform: " << *_train << std::endl;
}

cm::Platform::Platform() {
    num_id++;
    ID = "Platform " + num_id;
    _train = nullptr;
}

bool cm::Platform::trainArrive(cm::Train::Ptr&& t) {
    //TODO find out for checks what move assignment leaves behind to check on that.
    if (_train == nullptr)
        return false;
    else {
        _train = t;
        return true;
    }

}
//TODO this function is not correctly made, the train should be moved to simcontrol somehow, not set to null.
bool cm::Platform::trainDepart(cm::Train::Ptr&& t) {
    if (_train == nullptr)
        return false;
    else {
        _train = nullptr;
        return true;
    }
}

int cm::Platform::num_id = 0;

