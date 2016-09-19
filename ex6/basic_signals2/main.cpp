#include <iostream>
#include <boost/signals2.hpp>

void freeSlot(const std::string& sensorName, double sensorValue){
    std::cout << "im free..." << std::endl;
    std::cout << sensorName << ": " << sensorValue << std::endl;
}

struct slotFunctor {
    void operator()(const std::string &sensorName, double sensorValue) {
        std::cout << "I AM THE SLOTFUNCTOR!!!" << std::endl;
        std::cout << sensorName << ": " << sensorValue << std::endl;
    }
};

class SlotRefObj{
public:
    void slotMe(const std::string &sensorName, double sensorValue) {
        std::cout << "you have been referenced" << std::endl;
        std::cout << sensorName << ": " << sensorValue << std::endl;
    }
};
typedef boost::signals2::signal<void (const std::string&, double)> sensor_signal;

int main() {

    sensor_signal sensorSig;
    sensorSig.connect(freeSlot);
    sensorSig.connect(slotFunctor());
    std::shared_ptr<SlotRefObj> sro = std::make_shared<SlotRefObj>();
    sensorSig.connect(boost::bind(&SlotRefObj::slotMe, sro, _1, _2));
    sensorSig.connect(
            sensor_signal::slot_type(&SlotRefObj::slotMe, sro, _1, _2).track(sro));
    sensorSig("SaltinessSensor", 114);

    return 0;
}