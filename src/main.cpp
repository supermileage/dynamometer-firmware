#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "XPT2046_Touchscreen.h"
#include "Sensor/SensorOptical.h"

#include "application/ApplicationContext.h"
#include "graphics/colour.h"
#include "ui/UIEventHandler.h"
#include "System/HardwareInputSerial.h"
#include "System/InputManager.h"
#include "settings.h"

/* system resources */
Adafruit_ILI9341 tft = Adafruit_ILI9341(&SPI, TFT_DC, TFT_CS, TFT_RST);
XPT2046_Touchscreen ts(TOUCH_CS);

/* sensors */
SensorOptical optical(pio0, 0, OPTICAL_SENSOR_PIN);

/* io */
InputManager inputManager;
HardwareInputSerial inputSerial;

/* ui */
ApplicationContext context(inputManager, tft, ApplicationContext::MainMenu);

/* global variables */
uint64_t c0_lastUpdateTime = 0;
int c0_lastCount = 0;

/* Core0 */
void setup() {
	Serial.begin(115200);

	tft.begin();
	tft.setRotation(3);
	tft.fillScreen(COLOUR_BLACK);

	inputManager.registerInput(ID_SERIAL, &inputSerial);

	delay(1000);
	Handleable::beginAll();
}

void loop() {
	Handleable::handleAll();
}

/* Core1 */
void setup1() {
	UIEventHandler::instance().init();
}

void loop1() {
	UIEventHandler::instance().run();
}
