#ifndef _CIRCULAR_ELEMENT_H_
#define _CIRCULAR_ELEMENT_H_

#include "VisualElement.h"

class CircularElement : public VisualElement {
        CircularElement(Adafruit_GFX& display);
        ~CircularElement();
        
        /**
         * @brief get width of circular element relative to its top left corner
        */
        int16_t getWidth() override;

        /**
         * @brief get height of circular element relative to its top left corner
        */
        int16_t getHeight() override;

        /**
         * @brief get radius of circular element relative to its position
        */
        int16_t getRadius();
        
        /**
         * @brief set radius of circular element relative to its position
        */
        CircularElement& setRadius(int16_t radius);

        /**
         * @brief clear circular element from screen
        */
        void clear() override;

    protected:
        int16_t _radius = 0;

        /**
         * @brief internal draw method
         * 
         * @param colour background colour for draw
        */
        void _drawInternal(uint16_t colour) override;
};

#endif