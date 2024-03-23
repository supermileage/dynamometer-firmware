#ifndef _BPM_CONTROL_H_
#define _BPM_CONTROL_H_
#include "settings.h"

class BpmControl {
    private:    
        int _pinNum;
        bool _active = false;
    public:
        BpmControl (pin_size_t pinNum);
        void init ();
        void setControlSignal (int32_t signalStrength);
        void setActive (bool state);
};

#endif