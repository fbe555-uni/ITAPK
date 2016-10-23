//
// Created by felix on 10/17/16.
//


#include "station.hpp"

void cm::Station::Status() const{
    int i = 0;
    for (auto &item:platforms) {
        std::cout << "Status from " << item << ":" << std::endl;
        item.Status();
    }
}

cm::Station::Station(std::string n, int num_platforms) : platforms(), trainQueue() {
    name = n;
    for (; num_platforms > 0; num_platforms--) {
        platforms.push_back(Platform());

    }
}

//TODO implement add cargo functionality

std::list<cm::Platform> *cm::Station::getPlatforms() {
    return &platforms;
}

std::string cm::Station::getName() const{
    return name;
}

std::queue<cm::Train::Ptr> *cm::Station::getTrainQueue() {
    return &trainQueue;
}

bool cm::Station::isFull() {

    for (auto platform:platforms) {
        if (platform.isFree())
            return false;

    }
    return true;
}

bool cm::Station::isEmpty() {
    bool empty = true;
    for (auto platform:platforms) {
        if (!platform.isFree())
            empty = false;
    }
    return empty;
}

bool cm::Station::HasCargo() {
    bool hasCargo = false;
    for (auto platform:platforms) {
        if (!platform.getCargoList().empty())
            return true;
    }
    return hasCargo;
}


void cm::Platform::Status() const{
    std::cout << "Cargo on platform: " << std::endl;
    for (auto item:Platform::_cargo) {
        //TODO this reference i do not understand; at item
        std::cout << item << std::endl;
    }
    std::cout << "Train on platform: " << *_train << std::endl;
}

cm::Platform::Platform() {
    num_id++;
    ID = "Platform #" + std::to_string(num_id);
    //Smart pointer version of nullptr
    _train = cm::Train::Ptr();
}

bool cm::Platform::trainArrive(cm::Train::Ptr t) {
    if (!_train) {
        _train = t;
        return true;
    } else
        return false;
}

cm::Train::Ptr cm::Platform::trainDepart() {
    cm::Train::Ptr tmp_train = _train;
    if (!_train)
        return _train;
    else {
        _train = cm::Train::Ptr();
        return tmp_train;
    }
}

int cm::Platform::num_id = 0;

std::string cm::Platform::getID() const{
    return ID;
}

cm::Train::Ptr cm::Platform::getTrain() {
    return _train;
}

std::list<cm::Cargo::Ptr> cm::Platform::getCargoList() {
    return _cargo;
}

bool cm::Platform::isFree() {
    return _train == cm::Train::Ptr();
}
