#include "PollResponder.h"

#define NUM_SENSORS 1

#define ADDRESS 7
#define HEADER_LENGTH 3
#define SENSOR_DATA_LENGTH NUM_SENSORS * 2
#define DATA_BUFFER_LENGTH HEADER_LENGTH + SENSOR_DATA_LENGTH

#define HEADER0 0x3
#define HEADER1 0x5
#define HEADER2 0x7



/* Callbacks */
void receive(int bytes);
void request();
/* References for callbacks */
PollResponder* g_this;

PollResponder::PollResponder(TwoWire* wire, SensorForce* force) :
    _wire(wire), _force(force) { }

PollResponder::~PollResponder() { }

void PollResponder::begin() {
    _wire->begin(ADDRESS);
    _wire->onReceive(receiveRequest);
    g_sensorForce = _force;
}

void PollResponder::handle() {
    int bytesAvail = 0;
    if ((bytesAvail = _wire->available()) >= HEADER_LENGTH) {

        uint8_t buf[HEADER_LENGTH];
        _wire->readBytes(buf, HEADER_LENGTH);

        if (buf[0] != HEADER0 || buf[1] != HEADER1 || buf[2] != HEADER2) {
            _flush();
            return;
        }

        _sendResponse();
    }
}

void PollResponder::_sendResponse() {
    uint8_t buf[DATA_BUFFER_LENGTH];

    // pack buffer
    buf[0] = HEADER0;
    buf[1] = HEADER1;
    buf[2] = HEADER2;
    *(int16_t*)(buf + 3) = (int16_t)(_force->getForce() * 1000);

    _wire->write((char*)buf, DATA_BUFFER_LENGTH);
}

void PollResponder::_flush() {
    while(_wire->available()) {
        _wire->read();
    }
}