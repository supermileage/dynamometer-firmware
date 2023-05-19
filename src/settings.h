#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "Arduino.h"

/* IO */
#define TFT_DC 15
#define TFT_CS 17
#define TFT_RST 14
#define TOUCH_CS 13

#define OPTICAL_SENSOR_PIN 2
#define DEMUX_SELECT0 8
#define DEMUX_SELECT1 9


#define BUTTON_DEBOUNCE_MILLIS 50

// Input IDs
#define ID_SERIAL               0
#define ID_ROT_ENCODER          1
#define ID_ROTARY_EN_SELECT     2
#define ID_BACK                 3
#define ID_SELECT               4
#define ID_BRAKE_BUTTON         5
#define ID_BRAKE_POT            6

/* Debugging */
#define DEBUG_SERIAL_EN 1

#if DEBUG_SERIAL_EN
#define DEBUG_SERIAL_LN(x) Serial.println(x)
#else
#define DEBUG_SERIAL_LN(x) { }
#endif

#endif