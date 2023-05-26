#include "HardwareButton.h"

#include "settings.h"

HardwareButton::HardwareButton(pin_size_t pin, PinMode pinMode) {
		_pin = pin;
		_pinMode = pinMode;
}

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