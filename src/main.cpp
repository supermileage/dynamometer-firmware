#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "XPT2046_Touchscreen.h"
#include "Sensor/SensorOptical.h"

#include "application/MenuViewExample.h"
#include "graphics/colour.h"
#include "ui/UIEventHandler.h"
#include "settings.h"
#include "application/DisplayElement.h"

/* function declarations */
double getProtoRpm();

/* system resources */
Adafruit_ILI9341 tft = Adafruit_ILI9341(&SPI, TFT_DC, TFT_CS, TFT_RST);
XPT2046_Touchscreen ts(TOUCH_CS);

/* sensors */
SensorOptical optical(pio0, 0, OPTICAL_SENSOR_PIN);

/* ui */
// MenuViewExample menu(tft);
// UIEventHandler uiCore;
TextDisplay<double> rpmDisplay(getProtoRpm, 5, ILI9341_WHITE, 2, String("rpm "));
TextDisplay<double> velocityDisplay([]() { return optical.getLinearVelocity(); }, 5, ILI9341_WHITE, 2, String("vel "));

/* global variables */
uint64_t c0_lastUpdateTime = 0;
int c0_lastCount = 0;

/* Core0 */
void setup() {
	Serial.begin(115200);

	tft.begin();
	tft.setRotation(3);
	tft.fillScreen(COLOUR_BLACK);

	rpmDisplay.setPosition(30, 60);
	velocityDisplay.setPosition(30, 140);
	rpmDisplay.setMinTextLength(7); // 00.00
    velocityDisplay.setMinTextLength(5); // 00.00
	rpmDisplay.setBackgroundColour(COLOUR_BLACK);
	velocityDisplay.setBackgroundColour(COLOUR_BLACK);


	delay(1000);
	// uiCore.addEvent([]() { menu.init(); });
	Handleable::beginAll();
}

void loop() {
	if (millis() > c0_lastUpdateTime + 100) {
		c0_lastUpdateTime = millis();
		// uiCore.addEvent([]() { menu.run(); });

		rpmDisplay.draw(tft);
		velocityDisplay.draw(tft);
	}

	Handleable::handleAll();
}

/* Core1 */
// void setup1() {
// 	uiCore.init();
// }

// void loop1() {
// 	uiCore.run();
// }

/* function definitions */

#define INCHES_PER_METER 39.3701
#define WHEEL_CIRCUMFERENCE (21.0 * _PI)
#define PROTO_GEAR_RATIO 9.7

// convert linear velocity (m/s) to RPM
double getProtoRpm() {
	// (m/s) * 60s * (inches per meter) / (wheel diameter) * (gear ratio)
	return optical.getLinearVelocity() * 60.0 * INCHES_PER_METER / WHEEL_CIRCUMFERENCE * PROTO_GEAR_RATIO;
}