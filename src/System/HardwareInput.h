#ifndef _HARDWARE_INPUT_H_
#define _HARDWARE_INPUT_H_

#include <stdint.h>
#include <functional>
#include "settings.h"

typedef std::function<void(int32_t)> InputCallback;

class HardwareInput {
    public:
        virtual ~HardwareInput() { }
        virtual void init() = 0;
        virtual void run() = 0;
        void setAction(InputCallback action) { _action = action; }

    protected:
        InputCallback _action = [](int32_t) { }; // default action
};

class HardwareDemuxer {
    public:
        HardwareDemuxer(pin_size_t select0, pin_size_t select1) :
            _select0(select0), _select1(select1) { }

        ~HardwareDemuxer() { }

        void init() {
            pinMode(_select0, OUTPUT);
            pinMode(_select1, OUTPUT);
        }

        void setSelect(uint8_t selectId) {
            digitalWrite(_select0, static_cast<PinMode>(selectId & 0x1));
            digitalWrite(_select1, static_cast<PinMode>(selectId & 0x2));
        }

    private:
        pin_size_t _select0;
        pin_size_t _select1;
};

class HardwareDemuxButton : public HardwareInput {
    public:
        HardwareDemuxButton(InputCallback action, HardwareDemuxer& demuxer, pin_size_t pin, PinMode pinMode,
            uint8_t selectId) : _demuxer(demuxer), _pin(pin), _pinMode(pinMode), _selectId(selectId) {
            _action = action;
        }
		
        ~HardwareDemuxButton() { }

		void init() override {
            pinMode(_pin, _pinMode);
        }

		void run() override {
            _demuxer.setSelect(_selectId);
            PinStatus read = digitalRead(_pin);
	
            if (read != _lastRead && millis() > _lastReadMillis + BUTTON_DEBOUNCE_MILLIS) {
                (_action)(static_cast<uint32_t>(read));
                _lastReadMillis = millis();
                _lastRead = read;
            }
        }


    private:
        HardwareDemuxer& _demuxer;
        pin_size_t _pin;
        PinMode _pinMode;
        uint8_t _selectId;
        PinStatus _lastRead = LOW;
		uint32_t _lastReadMillis = 0;
};

#endif