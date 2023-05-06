#ifndef _UI_ELEMENT_H_
#define _UI_ELEMENT_H_

#include "VisualElement.h"

/**
 * @brief base class for interactive UI elements
*/
class UIElement : public VisualElement {
    public:
        UIElement(Point pos, int16_t width, int16_t height) : VisualElement(pos, width, height) { };
        virtual ~UIElement() { }
        virtual void focus() = 0;
        virtual void unfocus() = 0;
        virtual void select() = 0;
};

#endif
