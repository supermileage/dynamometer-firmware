#include "HardwareButton.h"

#include "settings.h"

HardwareButton::HardwareButton(InputCallback action, pin_size_t pin, PinMode pinMode) {
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
	
	if (read != _lastRead && millis() > _lastReadMillis + BUTTON_DEBOUNCE_MILLIS) {
		(_action)(static_cast<uint32_t>(read));
		_lastReadMillis = millis();
		_lastRead = read;
	}
}