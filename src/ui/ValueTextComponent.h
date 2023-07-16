#ifndef _VALUE_TEXT_COMPONENT_H_
#define _VALUE_TEXT_COMPONENT_H_

#include "TextComponent.h"

/**
 * @brief specialized text class which is optimized to represent numerical values (time, decimals, ints, etc..)
 * @note  unlike TextComponent, ValueTextComponent sets all alpha-numeric characters to be the same width;
 *        does not wrap text if string goes beyond bounds of screen
*/
class ValueTextComponent : public TextComponent {
    public:
        /**
         * @brief computes and returns Point with x, y representing width and height of display string
        */
        ui_util::Point computeDisplaySize() override;

    private:
        /**
         * @brief overridden _drawInternal method checks whether or not to call _drawOptimized
        */
        void _drawInternal(TFT_eSPI& display, uint16_t colour) override;

        /**
         * @brief specialized draw method which only erases and redraws characters whose values have changed
        */
        void _drawOptimized(TFT_eSPI& display, uint16_t colour, int16_t x, int16_t y);

        /**
         * @brief draws entire string display called on initial draw or after font / string length changed
        */
        void _redraw(TFT_eSPI& display, uint16_t colour, int16_t x, int16_t y);
};

#endif