#ifndef _HARDWARE_INPUT_SERIAL_H_
#define _HARDWARE_INPUT_SERIAL_H_

#include "Arduino.h"
#include "HardwareInput.h"

/**
 * @brief serial input class which reads user input from serial monitor
 * 
 * @note only passes individual characters to input callback: ui controller must decide what
 * to do with the information
*/
class HardwareInputSerial : public HardwareInput {
    public:
        ~HardwareInputSerial() { }

        void init() override { }

        void run() override {
            while (Serial.available()) {
                (_action)((input_data_t)Serial.read());
            }
        }
};

#endif