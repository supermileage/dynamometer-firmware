#ifndef _HARDWARE_DEMUXER_H_
#define _HARDWARE_DEMUXER_H_

#include "Arduino.h"

/**
 * @brief provides means of controlling select pins of dyno demux ic
*/
class HardwareDemuxer {
    public:
        HardwareDemuxer(pin_size_t select0, pin_size_t select1, pin_size_t output) :
            _select0(select0), _select1(select1), _output(output) { }

        ~HardwareDemuxer() { }

        inline void init() {
            pinMode(_select0, OUTPUT);
            pinMode(_select1, OUTPUT);
            pinMode(_output, INPUT_PULLDOWN);
        }

        /**
         * @brief sets select pins to id
         * 
         * @note id must be unsigned 2-bit value: 0b00, 0b01, 0b10, or 0b11
        */
        inline void setSelect(uint8_t selectId) {
            digitalWrite(_select0, static_cast<PinStatus>(selectId & 0x1));
            digitalWrite(_select1, static_cast<PinStatus>(selectId & 0x2));
        }

        inline pin_size_t getOutputPin() {
            return _output;
        }

    private:
        pin_size_t _select0;
        pin_size_t _select1;
        pin_size_t _output;
};

#endif