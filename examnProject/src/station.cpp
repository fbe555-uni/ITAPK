//
// Created by felix on 10/17/16.
//


#include "station.h"

void CMS::Station::Status() {
    int i = 0;
    for(auto item:Station::_platforms){
        std::cout << "Status from platform " << i++ << ":" << std::endl;
        item.Status();
    }
}

CMS::Platform::Platform() {

}

void CMS::Platform::Status() {
    std::cout << "Cargo on platform: " << std::endl;
    for(auto item:Platform::_cargo){
        std::cout << item << std::endl;
    }
    std::cout << "Train on platform: " <<
}
