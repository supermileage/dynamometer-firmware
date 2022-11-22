#include "settings.h"

#include "System/Handleable.h"
#include "Sensor/SensorForce.h"
#include "Sensor/SensorRpm.h"

/* Forward declarations */
// void toggleBrakeModule();

/* Timing */
#define ARR_SIZE 150
uint64_t g_loopArr[ARR_SIZE] = { };
uint8_t g_loopIndex = 0;
uint64_t g_lastPrintTime = 0;
uint64_t g_lastLoopTime = 0;
bool g_reset = false;

/* Objects */
SensorForce sensorforce(FORCE_SENSOR, OUTPUT);
SensorRpm sensorRpm();

void setup() {
	Serial.begin(9600);
}

void loop() {
	if (g_reset) {
		g_loopIndex = 0;
		g_lastLoopTime = micros();
		g_reset = false;
	} else {
		g_loopArr[g_loopIndex++] = micros();
		Handleable::handleAll();
	}
	
	#if DEBUG_SERIAL_EN
	if (g_loopIndex == ARR_SIZE) {
		uint64_t sum = 0;
		uint64_t maxTime = 0;

		for (uint8_t i = 0; i < ARR_SIZE; i++) {
			sum += (g_loopArr[i] - g_lastLoopTime);
			maxTime = max(g_loopArr[i] - g_lastLoopTime, maxTime);
			g_lastLoopTime = g_loopArr[i];
		}

		g_reset = true;
		if (millis() > g_lastPrintTime + 2000) {
			g_lastPrintTime = millis();
			DEBUG_SERIAL_LN("Average loop time: " + String((unsigned long)(sum / ARR_SIZE)));
			DEBUG_SERIAL_LN("Max loop time: " + String((unsigned long)(maxTime)));
		}
	}
	#endif
}

/* Button Callback */
// void toggleBrakeModule() {
// 	g_runBrakeModule = !g_runBrakeModule;

// 	if (g_runBrakeModule) {
// 		digitalWrite(LED_BUILTIN, HIGH);
// 	}
// 	else {
// 		digitalWrite(BRAKE_CONTROL_PIN, HIGH);
// 		digitalWrite(LED_BUILTIN, LOW);
// 	}
// 	Serial.println(String("Turning brake module ") + String((g_runBrakeModule ? "On" : "Off")));
// }