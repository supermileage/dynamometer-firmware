#include <stdint.h>
#include "settings.h"
#include "System/Button.h"
#include "Sensor/SensorForce.h"

/* Forward declarations */
void toggleBrakeModule();

/* Global variables */
bool g_runBrakeModule = false;
int64_t g_lastBrakeWrite = 0;
uint64_t g_lastForceReadTime = 0;

Button button(BUTTON_PIN, INPUT_PULLUP, toggleBrakeModule);
SensorForce sensorforce(FORCE_SENSOR, OUTPUT);

void setup() {
	Serial.begin(9600);
	pinMode(BRAKE_CONTROL_PIN, OUTPUT);
	pinMode(LED_BUILTIN, OUTPUT);

	button.init();
}

void loop() {
	button.run();

	sensorforce.handle();
}

/* Button Callback */
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