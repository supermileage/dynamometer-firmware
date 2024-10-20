#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "XPT2046_Touchscreen.h"
#include "Sensor/SensorOptical.h"

#include "settings.h"

/* system resources */
Adafruit_ILI9341 tft = Adafruit_ILI9341(&SPI, TFT_DC, TFT_CS, TFT_RST);
XPT2046_Touchscreen ts(TOUCH_CS);

/* sensors */
SensorOptical optical(pio0, 0, OPTICAL_SENSOR_PIN);

/* ui */


/* global variables */
uint64_t c0_lastUpdateTime = 0;
int c0_lastCount = 0;

/* Core0 */
void setup() {
	Serial.begin(115200);
}

void loop() {
	Handleable::handleAll();
}


/* Core1 */
void setup1() {

}

