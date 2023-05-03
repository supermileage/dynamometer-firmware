#include "Button.h"

#define DEBOUNCE_TIME 250

Button::Button(int32_t pin, PinMode pinMode, void (*action)(void)) : _pin(pin), _pinMode(pinMode), _action(action) {  }

Button::~Button() { }

void Button::init() {
	pinMode(_pin, _pinMode);
}

void Button::run() {
	PinStatus read = digitalRead(_pin);
	uint64_t currentTime = millis();

	if (currentTime > _lastReadHigh + DEBOUNCE_TIME && read == LOW) {
		(_action)();
		_lastReadHigh = currentTime;
	}
}