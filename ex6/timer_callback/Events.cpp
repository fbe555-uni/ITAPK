#include <ostream>
#include <ctime>

#include "Events.hpp"

std::ostream &operator<<(std::ostream &os, const Event &ev) {
    std::time_t creationTime = std::chrono::system_clock::to_time_t(ev.creationTime());
    os << "Event: " << std::ctime(&creationTime);

    return os;
}

std::ostream &operator<<(std::ostream &os, const EventOther &ev) {
    std::time_t creationTime = std::chrono::system_clock::to_time_t(ev.creationTime());
    os << "EventOther: " << std::ctime(&creationTime);

    return os;
}

