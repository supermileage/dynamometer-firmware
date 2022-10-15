#include <stdint.h>

#include "Arduino.h"
#include "settings.h"

#define DEBOUNCE_TIME 250
#define BRAKE_MODULE_PIN 2
#define BUTTON_PIN PIN_A0

/* Helper Classes */
class Button {
	public:
		Button(int32_t pin, PinMode pinMode, void (*action)(void)) : _pin(pin), _pinMode(pinMode), _action(action) {  }
		~Button() { }
		void init() {
			pinMode(_pin, _pinMode);
		}
		void run() {
			PinStatus read = digitalRead(_pin);
			uint64_t currentTime = millis();

			if (currentTime > _lastReadHigh + DEBOUNCE_TIME && read == LOW) {
				(_action)();
				_lastReadHigh = currentTime;
			}
		}

	private:
		int32_t _pin;
		PinMode _pinMode;
		void (*_action)(void) = NULL;
		uint64_t _lastReadHigh = 0;
};

/* Forward declarations */
void toggleBrakeModule();

/* Arduino Code */
Button button(BUTTON_PIN, INPUT_PULLUP, toggleBrakeModule);

void setup() {
	// pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(9600);
	pinMode(BRAKE_MODULE_PIN, OUTPUT);
	pinMode(LED_BUILTIN, OUTPUT);

	pinMode(6, OUTPUT);
	pinMode(A7, INPUT);
	button.init();
}

/* Globals */
uint64_t g_lastPrintMillis = 0;
uint64_t g_printInterval = 2000;
bool g_runModule = false;

void loop() {
	button.run();

	int pot_val = (int)((float)(analogRead(A7)) * 255/1023);
	if (g_runModule) {
		analogWrite(6, 255 - pot_val);
	}

	if (millis() > g_lastPrintMillis + g_printInterval) {
		Serial.println("Potentiometer value : " + String(pot_val));
		g_lastPrintMillis = millis();
	}
}

/* Helper Functions */
void toggleBrakeModule() {
	g_runModule = !g_runModule;

	if (g_runModule) {
		digitalWrite(BRAKE_MODULE_PIN, HIGH);
		digitalWrite(LED_BUILTIN, HIGH);
	}
	else {
		digitalWrite(BRAKE_MODULE_PIN, LOW);
		digitalWrite(LED_BUILTIN, LOW);
	}

	Serial.println(String("Turning brake module ") + String((g_runModule ? "On" : "Off")));
}