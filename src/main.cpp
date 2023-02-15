#include <Wire.h>

#include "settings.h"
#include "Sensor/SensorForce.h"
#include "Sensor/SensorOptical.h"
#include "Sensor/PollResponder.h"

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
SensorForce sensorForce(FORCE_SENSOR, OUTPUT);
SensorOptical sensorRpm(OPTICAL_SENSOR, INPUT);

/* Global Variables */
unsigned long g_lastReadTime = 0;

void setup() {
	Serial.begin(9600);
    sensorForce.begin();
    sensorRpm.begin();
    PollResponder::instance().begin(&Wire, &sensorForce, &sensorRpm);
}

void loop() {
	sensorForce.handle();
	sensorRpm.handle();

	if(millis() > g_lastReadTime + 1250) {
        g_lastReadTime = millis();
        // DEBUG_SERIAL_LN("Force: " + String(sensorForce.getForce()));
        DEBUG_SERIAL_LN("Angular Velocity: " + String(sensorRpm.getAngularVelocity()));
	}	
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