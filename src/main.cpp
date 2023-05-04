#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "XPT2046_Touchscreen.h"
#include "Sensor/SensorOptical.h"

#include "settings.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 15 //5
#define TFT_CS 17 //3
#define TFT_MOSI 19 //6
#define TFT_MISO 16 //9
#define TFT_CLK 18 //7
#define TFT_RST 14 //4
#define TOUCH_CS 13

#define SENSOR_POLLING_INTERVAL 200

/* Globals */
uint64_t g_lastUpdateTime = 0;
int g_lastCount = 0;

// SensorOptical optical(pio0, 0, OPTICAL_SENSOR_PIN);

Adafruit_ILI9341 tft = Adafruit_ILI9341(&SPI, TFT_DC, TFT_CS, TFT_RST);
XPT2046_Touchscreen ts(TOUCH_CS);

void setup() {
	Serial.begin(115200);

	tft.begin();
	tft.setRotation(3);

	ts.begin(SPI);
	ts.setRotation(3);

	Wire.begin();
	Wire.setTimeout(1000);
	pinMode(2, INPUT);
    
    // add labels for force and angular velocity
	tft.fillScreen(ILI9341_BLACK);
	tft.setTextSize(2);
	tft.setCursor(20, 40);
	tft.write("Pressure = ");
	tft.setCursor(20, 100);
	tft.write("x = ");
	tft.setCursor(20, 160);
	tft.write("y = ");
}

void loop()
{
	if (ts.touched()) {
		// tft.fillRect(200,40,260,60,ILI9341_BLACK);
		// tft.fillRect(200,100,260,200,ILI9341_BLACK);
		// tft.fillRect(200,160,260,180,ILI9341_BLACK);

		TS_Point p = ts.getPoint();
    	Serial.print("Pressure = ");
    	Serial.print(p.z);
    	Serial.print(", x = ");
    	Serial.print(p.x);
    	Serial.print(", y = ");
    	Serial.print(p.y);
    	Serial.println();

		// tft.setCursor(200, 40);
		// tft.write(String(p.z).c_str());
		// tft.setCursor(200, 100);
		// tft.write(String(p.x).c_str());
		// tft.setCursor(200, 160);
		// tft.write(String(p.y).c_str());
		delay(500);
	}
}