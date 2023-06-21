#ifndef _RECTANGULAR_ELEMENT_H_
#define _RECTANGULAR_ELEMENT_H_

#include "VisualElement.h"

class RectangularElement : public VisualElement {
    public:
        RectangularElement(Adafruit_GFX& display);
        ~RectangularElement(); 

        /**
         * @brief get width of rectangular element relative to its position
        */
        int16_t getWidth() override;

        /**
         * @brief get height of rectangular element relative to its position
        */
        int16_t getHeight() override;
        
        /**
         * @brief set width of rectangular element relative to its position
        */
        RectangularElement& setWidth(int16_t width);

        /**
         * @brief set height of rectangular element relative to its position
        */
        RectangularElement& setHeight(int16_t height);

        /**
         * @brief clear rectangular element from screen
        */
        void clear() override;

    protected:
        int16_t _width = 0;
        int16_t _height = 0;

        /**
         * @brief internal draw method
         * 
         * @param colour background colour for draw
        */
        void _drawInternal(uint16_t colour) override;
};

#endif