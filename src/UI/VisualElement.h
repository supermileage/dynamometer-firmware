#ifndef _VISUAL_ELEMENT_H_
#define _VISUAL_ELEMENT_H_

#include "Adafruit_ILI9341.h"
#include "ui_util.h"

using namespace ui_util;

/**
 * @brief base displayable element class
*/
class VisualElement {
    public:
        VisualElement(Adafruit_ILI9341& display);
        virtual ~VisualElement();
        Point getPosition();
        void setPosition(Point pos);
        int16_t getWidth();
        void setWidth(int16_t width);
        int16_t getHeight();
        void setHeight(int16_t height);
        virtual void draw() = 0;
        virtual void clear() = 0;

    protected:
        Adafruit_ILI9341& _display;
        Point _position = Point { 0, 0 };
        int16_t _width = 0;
        int16_t _height = 0;

        /**
         * @brief resize event handler to be implemented in derived classes
        */
        virtual void _onResize() = 0;
};

#endif