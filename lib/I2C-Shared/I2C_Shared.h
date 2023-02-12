#ifndef _I2C_SHARED_H_
#define _I2C_SHARED_H_

#include <stdint.h>

#define NUM_SENSORS 2

#define ADDRESS 7
#define HEADER_LENGTH 3
#define SENSOR_DATA_LENGTH NUM_SENSORS * sizeof(int32_t)
#define DATA_BUFFER_LENGTH HEADER_LENGTH + SENSOR_DATA_LENGTH

#define HEADER0 0xD
#define HEADER1 0x11
#define HEADER2 0x1D

#endif