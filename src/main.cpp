#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#include "settings.h"
#include "I2C_Shared.h"
#include "PIO/pio_counter_program.pio.h"

// For the Adafruit shield, these are the default.
#define TFT_DC 15 //5
#define TFT_CS 17 //3
#define TFT_MOSI 19 //6
#define TFT_MISO 16 //9
#define TFT_CLK 18 //7
#define TFT_RST 14 //4

#define SENSOR_POLLING_INTERVAL 200

/* Globals */
uint64_t g_lastUpdateTime = 0;
int g_lastCount = 0;

PIO pio = pio0;

Adafruit_ILI9341 tft = Adafruit_ILI9341(&SPI, TFT_DC, TFT_CS, TFT_RST);

void setup() {
	Serial.begin(115200);
	tft.begin();
	tft.setRotation(3);
	Wire.begin();
	Wire.setTimeout(1000);
	pinMode(2, INPUT);
    
    // add labels for force and angular velocity
	tft.fillScreen(ILI9341_BLACK);
	tft.setTextSize(2);
	tft.setCursor(30, 30);
	tft.write("Force: ");
	tft.setCursor(30, 120);
	tft.write("Ang.V: ");

	// set up pio
	pinMode(OPTICAL_SENSOR_PIN, INPUT);
	uint offset = pio_add_program(pio, &pio_counter_program);
	pio_counter_init(pio, 0, offset, OPTICAL_SENSOR_PIN, 0);
}

void loop(void)
{
	int count = pio_counter_get_count(pio, 0);

	if (count != g_lastCount)
	{
		DEBUG_SERIAL_LN("pio_counter: " + String(count));
		g_lastCount = count;
	}

	if (millis() > g_lastUpdateTime + SENSOR_POLLING_INTERVAL)
	{
		g_lastUpdateTime = millis();
		Wire.requestFrom(ADDRESS, DATA_BUFFER_LENGTH);

		if (Wire.available())
		{
			uint8_t buf[DATA_BUFFER_LENGTH];
			int n = Wire.readBytes(buf, DATA_BUFFER_LENGTH);
			float force = ((float)*(int32_t *)(buf + 3)) / FORCE_SCALING;
			float av = ((float)*(int32_t *)(buf + 7)) / ANGULAR_VELOCITY_SCALING;

			DEBUG_SERIAL_LN("Read " + String(n) + " bytes from I2C buffer");
			DEBUG_SERIAL_LN("Force: " + String(*(int32_t *)(buf + 3)) + " -- rpm: " + String(*(int32_t *)(buf + 7)));

			tft.setTextColor(ILI9341_CYAN);
			tft.fillRect(100, 30, 200, 144, ILI9341_BLACK);
			tft.setTextSize(3);

			tft.setCursor(100, 30);
			tft.write(String(force, 3).c_str());

			tft.setCursor(100, 120);
			tft.write(String(av, 3).c_str());
		}
	}
}