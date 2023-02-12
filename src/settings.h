#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <Arduino.h>

/* IO */
#define BRAKE_CONTROL_PIN 6
#define BUTTON_PIN PIN_A0
#define POT_PIN PIN_A7
#define FORCE_SENSOR PIN_A5
#define OPTICAL_SENSOR 3

/* Debugging */
#define DEBUG_SERIAL_EN 1

#if DEBUG_SERIAL_EN
#define DEBUG_SERIAL_LN(x) Serial.println(x)
#else
#define DEBUG_SERIAL_LN(x) { }
#endif

/* Arduino */
#ifdef ARDUINO_PLATFORM
typedef int PinMode;
typedef int pin_size_t;
typedef int PinStatus;
#endif

#endif