#ifndef _BPM_CONTROL_H_
#define _BPM_CONTROL_H_
#include "settings.h"

#define ANALOG_MAX 1023
#define ANALOG_FREQ 20000

class BpmControl {
    private:    
        int _pinNum;
        bool _active = false;
        uint16_t _controlSignal = 0;
    public:
        BpmControl (pin_size_t pinNum);
        void init ();
        void setControlSignal (int32_t signalStrength);
        int32_t getControlSignal(void);
        void setActive (bool state);
        bool getStatus(void);
};

#endif