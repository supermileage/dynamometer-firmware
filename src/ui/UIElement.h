#ifndef _UI_ELEMENT_H_
#define _UI_ELEMENT_H_

#include <functional>

#include "VisualElement.h"

/**
 * @brief base class for interactive UI elements
*/
class UIElement : public VisualElement {
    public:
        UIElement(Adafruit_ILI9341& display) : VisualElement(display) { }

        virtual ~UIElement() { }
        
        /**
         * @brief pure virtual function so derived classes can define custom focus graphics
        */
        virtual void focus() = 0;

        /**
         * @brief pure virtual function so derived classes can define custom unfocus graphics
        */
        virtual void unfocus() = 0;

        /**
         * @brief pure virtual function so derived classes can define custom select animation
        */
        virtual void select() = 0;
};

#endif
