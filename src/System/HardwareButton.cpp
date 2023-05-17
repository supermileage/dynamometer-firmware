#include "HardwareButton.h"

#define DEBOUNCE_TIME 50

HardwareButton::HardwareButton(InputCallback action, int32_t pin, PinMode pinMode) {
		_action = action;
		_pin = pin;
		_pinMode = pinMode;
}

HardwareButton::~HardwareButton() { }

void HardwareButton::init() {
	pinMode(_pin, _pinMode);
}

void HardwareButton::run() {
	PinStatus read = digitalRead(_pin);
	
	if (read != _lastRead && millis() > _lastReadMillis + DEBOUNCE_TIME) {
		(_action)((input_data_t)read);
		_lastReadMillis = millis();
		_lastRead = read;
	}
}