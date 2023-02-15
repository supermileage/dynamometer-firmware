#include "Wire.h"
#include "PollResponder.h"
#include "I2C_Shared.h"

/* References for callbacks */
PollResponder* PollResponder::_instance = nullptr;
TwoWire* PollResponder::_wire;
SensorForce* PollResponder::_force;
SensorRpm* PollResponder::_rpm;

PollResponder::PollResponder() { }

PollResponder::~PollResponder() { }

PollResponder& PollResponder::instance() {
    if (!_instance) {
        _instance = new PollResponder();
    }
    return *_instance;
}

void PollResponder::begin(TwoWire* wire, SensorForce* force, SensorRpm* rpm) {
    _wire = wire;
    _force = force;
    _rpm = rpm;

    _wire->begin(ADDRESS);
    _wire->onRequest([]() { PollResponder::instance()._sendResponse(); });
}

void PollResponder::_sendResponse() {
    uint8_t buf[DATA_BUFFER_LENGTH];

    // pack buffer
    buf[0] = HEADER0;
    buf[1] = HEADER1;
    buf[2] = HEADER2;
    *(int32_t*)(buf + 3) = (int32_t)(_force->getForce() * 1000);
    *(int32_t*)(buf + 7) = (int32_t)(_rpm->getRpm() * 100);

    _wire->write((char*)buf, DATA_BUFFER_LENGTH);
}

void PollResponder::_flush() {
    while(_wire->available()) {
        _wire->read();
    }
}