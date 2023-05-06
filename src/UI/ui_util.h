#ifndef _UI_UTIL_H_
#define _UI_UTIL_H_

#include <stdint.h>

namespace ui_util {
    struct Point {
        int16_t x;
        int16_t y;
    };


    /**
     * @brief represents 16-bit 5-6-5 rgb colour
     * 
     * @note value ranges: r in [0,31], g in [0,63], b in [0,31]
    */
    struct RGBColour16 {
        uint8_t r;
        uint8_t g;
        uint8_t b;

        /**
         * @brief colour copy-constructor
        */
        RGBColour16(uint16_t colour) {
            r = colour >> 11;
            g = (colour >> 5) & 0x3F;
            b = colour & 0x1F;
        }

        /**
         * @brief converts colour data to 5-6-5 format
         * 
         * @note will stomp values outside of ranges specified above
        */
        uint16_t toColour16() {
            return (r << 11) | ((g & 0x3F) << 5) | (b & 0x1F);
        }
    };
}

#endif