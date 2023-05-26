#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "Arduino.h"

/* Display */
#define LCD_CS 17
#define LCD_DC 21
#define LCD_RST 20
#define TOUCH_CS 13

#define OPTICAL_SENSOR_PIN 2
#define DEMUX_SELECT0 8
#define DEMUX_SELECT1 9


#define BUTTON_DEBOUNCE_MILLIS 50

// UI Input IDs (must be sequential)
#define ID_SERIAL               0
#define ID_ROT_ENCODER          1
#define ID_ROTARY_EN_SELECT     2
#define ID_BACK                 3
#define ID_SELECT               4
#define ID_BRAKE_BUTTON         5
#define ID_BRAKE_POT            6
#define NUM_INPUT_IDS           7

/* Debugging */
#define DEBUG_SERIAL_EN 1

#if DEBUG_SERIAL_EN
#define DEBUG_SERIAL_LN(x) Serial.println(x)
#define DEBUG_SERIAL(x) Serial.print(x)
#else
#define DEBUG_SERIAL_LN(x) { }
#define DEBUG_SERIAL(x) { }
#endif

#define DEBUG_STATE_TRANSITION_LN(x) Serial.println(x)
// #define DEBUG_STATE_TRANSITION_LN(x) { }

#endif