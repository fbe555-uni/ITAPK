//
// Created by felix on 10/17/16.
//


#include "station.hpp"
template<typename T, typename ... R>
void test(T first, R... rest){
    test(rest...);
};

void test(){
    std::cout << "Rock bottom";
}
void cm::Station::Status() const{
    int i = 0;
    for (auto &item:platforms) {
        tp::print("Status from ", item, ":", "\n\r");
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
        if (!platform.getCargoList()->empty())
            return true;
    }
    return hasCargo;
}


void cm::Platform::Status() const{
    tp::print("Cargo on platform: ", "\n\r");
    for (auto item:Platform::_cargo) {
        //TODO this reference i do not understand; at item
        tp::print(item, "\n\r");
    }
    tp::print("Train on platform: ", _train, "\n\r");
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

std::list<cm::Cargo::Ptr>* cm::Platform::getCargoList() {
    return &_cargo;
}


void cm::Platform::addCargo(const std::list<cm::Cargo::Ptr>& cargo){
    for(auto c : cargo){
        //make a new copy of each element in the list
        _cargo.push_back(cm::Cargo::Ptr(new cm::Cargo(*c)));
    }
}

bool cm::Platform::isFree() {
    return _train == cm::Train::Ptr();
}
