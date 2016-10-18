//
// Created by felix on 10/17/16.
//


#include "station.hpp"

void ST3000::Station::Status() {
    int i = 0;
    for (auto item:Station::_platforms) {
        std::cout << "Status from platform " << i++ << ":" << std::endl;
        item.Status();
    }
}

ST3000::Station::Station(std::string n) {
    _name = n;
}

void ST3000::Platform::Status() {
    std::cout << "Cargo on platform: " << std::endl;
    for (auto item:*Platform::_cargo) {
        std::cout << &item << std::endl;
    }
    std::cout << "Train on platform: " << _train << std::endl;
}

ST3000::Platform::Platform(){
    id++;
    ID = "Platform " + id;
}

int ST3000::Platform::id = 0;
