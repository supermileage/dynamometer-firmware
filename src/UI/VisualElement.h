#ifndef _VISUAL_ELEMENT_H_
#define _VISUAL_ELEMENT_H_

#include "ui_util.h"

using namespace ui_util;

/**
 * @brief base displayable element class
*/
class VisualElement {
    public:
        VisualElement(Point pos, int16_t width, int16_t height);
        virtual ~VisualElement();
        Point getPosition();
        void setPosition(Point pos);
        int16_t getWidth();
        int16_t getHeight();
        virtual void draw() = 0;
        virtual void clear() = 0;

    private:
        Point _position = Point { 0, 0 };
        int16_t _width = 0;
        int16_t _height = 0;
};

#endif