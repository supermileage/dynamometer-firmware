#include "KillSwitch.h"
#include "BpmControl.h"

#include "settings.h"

/* Hardware Button */
KillSwitch::KillSwitch(pin_size_t killSwitchPin)
	: _killSwitchPin(killSwitchPin)  { }

KillSwitch::~KillSwitch() { }

void KillSwitch::init() {
    pinMode(_killSwitchPin, INPUT);
    state = 0;
}

void KillSwitch::run() {
	// sets the select pins on the demux to read this button

	if (!digitalRead(_killSwitchPin)) {
		setControlSignal(ANALOG_MAX);
        state = 1;
	}

    // move later

    if (state == 1) {

    }
}

