//
// Created by felix on 10/17/16.
//


#include "station.hpp"

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

bool cm::Station::hasCargo() {
    bool hasCargo = false;
    for (auto platform:platforms) {
        if (!platform.getCargoList()->empty())
            return true;
    }
    return hasCargo;
}

void cm::Station::Status() {
    tp::print("Status from platforms: ");
    for (auto& platform:platforms) {
        platform.Status();
    }

}


void cm::Platform::Status() const{
    tp::print("Cargo on ", this, ":");
    for (auto& item:Platform::cargo) {
        tp::print(item);
    }
    tp::print("Train on ",this, ": ", train);
}

cm::Platform::Platform() {
    num_id++;
    id = "Platform #" + std::to_string(num_id);
    //Smart pointer version of nullptr
    train = cm::Train::Ptr();
}

bool cm::Platform::trainArrive(cm::Train::Ptr t) {
    if (!train) {
        train = t;
        return true;
    } else
        return false;
}

cm::Train::Ptr cm::Platform::trainDepart() {
    cm::Train::Ptr tmp_train = train;
    if (!train)
        return train;
    else {
        train = cm::Train::Ptr();
        return tmp_train;
    }
}

int cm::Platform::num_id = 0;

std::string cm::Platform::getID() const{
    return id;
}

cm::Train::Ptr cm::Platform::getTrain() {
    return train;
}

std::list<cm::Cargo::Ptr>* cm::Platform::getCargoList() {
    return &cargo;
}

const std::list<cm::Cargo::Ptr>* cm::Platform::getConstCargoList() const{
    return &cargo;
}


void cm::Platform::addCargo(std::list<cm::Cargo::Ptr>& c) {
    cargo.splice(cargo.end(), c);
}

bool cm::Platform::isFree() {
    return train == cm::Train::Ptr();
}
