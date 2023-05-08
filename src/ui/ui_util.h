#ifndef _UI_UTIL_H_
#define _UI_UTIL_H_

#include <stdint.h>
#include "Adafruit_GFX.h"

namespace ui_util {

    /**
     * @brief represents a point with x and y coordinates
    */
    struct Point {
        int16_t x;
        int16_t y;
    };

    /**
     * @brief represents 16-bit 5-6-5 rgb colour
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

    /**
     * @brief computes the pixel width and height of single character for given font
    */
    static inline Point computeCharacterDimensions(const GFXfont* font, uint8_t c, uint8_t sizeX, uint8_t sizeY) {
        uint8_t first = (uint8_t)(font->first);
        if (c < first || c > (uint8_t)(font->last)) {
            return Point { 0, 0 };
        }

        GFXglyph *glyph =  font->glyph + (c - first);
        int16_t w = glyph->xAdvance * (int16_t)sizeX;
        int16_t h = glyph->height * (int16_t)sizeY;
        return Point { w, h };
    }

    /**
     * @brief computes the pixel width and height of string for given font
    */
    static inline Point computeStringDimensions(const GFXfont* font, String str, uint8_t sizeX, uint8_t sizeY) {
        int16_t width = 0;
        int16_t maxHeight = 0;

        for (unsigned int i = 0; i < str.length(); i++) {
            Point cur = computeCharacterDimensions(font, (uint8_t)str[i], sizeX, sizeY);
            width += cur.x;
            if (cur.y > maxHeight) {
                maxHeight = cur.y;
            }
        }

        return Point { width, maxHeight };
    }
}

#endif