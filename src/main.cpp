#include <stdint.h>

#include "Arduino.h"
#include "settings.h"

#define PRINT_INTERVAL 2000
#define BRAKE_THRESHOLD 5
#define DEBOUNCE_TIME 250
#define BRAKE_CONTROL_PIN 6
#define BUTTON_PIN PIN_A0
#define POT_PIN PIN_A7

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

/* Global variables */
bool g_runBrakeModule = false;
int64_t g_lastBrakeWrite = 0;
uint64_t g_lastPrintTime = 0;

/* Arduino Code */
Button button(BUTTON_PIN, INPUT_PULLUP, toggleBrakeModule);

void setup() {
	// pinMode(LED_BUILTIN, OUTPUT);
	Serial.begin(9600);
	pinMode(BRAKE_CONTROL_PIN, OUTPUT);
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(POT_PIN, INPUT);
	button.init();
}

void loop() {
	button.run();

	if (g_runBrakeModule) {
		int64_t brakeVal = map(analogRead(POT_PIN), 0, 1023, 0, 255);

		if (brakeVal != g_lastBrakeWrite) {
			if (brakeVal < BRAKE_THRESHOLD)
				digitalWrite(BRAKE_CONTROL_PIN, HIGH);
			else
				analogWrite(BRAKE_CONTROL_PIN, 255 - brakeVal);

			g_lastBrakeWrite = brakeVal;
		}
	}
}

/* Helper Functions */
void toggleBrakeModule() {
	g_runBrakeModule = !g_runBrakeModule;

	if (g_runBrakeModule) {
		digitalWrite(LED_BUILTIN, HIGH);
	}
	else {
		digitalWrite(BRAKE_CONTROL_PIN, HIGH);
		digitalWrite(LED_BUILTIN, LOW);
	}

	Serial.println(String("Turning brake module ") + String((g_runBrakeModule ? "On" : "Off")));
}