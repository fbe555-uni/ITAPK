//
// Created by felix on 10/17/16.
//


#include "station.hpp"

void cm::Station::Status() {
    int i = 0;
    for (auto item:Station::_platforms) {
        std::cout << "Status from platform " << i++ << ":" << std::endl;
        item.Status();
    }
}

cm::Station::Station(std::string n) {
    _name = n;
}

void cm::Platform::Status() {
    std::cout << "Cargo on platform: " << std::endl;
    for (auto item:*Platform::_cargo) {
        std::cout << &item << std::endl;
    }
    std::cout << "Train on platform: " << _train << std::endl;
}

cm::Platform::Platform() {
    id++;
    ID = "Platform " + id;
}

int cm::Platform::id = 0;
