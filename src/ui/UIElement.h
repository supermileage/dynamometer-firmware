#ifndef _UI_ELEMENT_H_
#define _UI_ELEMENT_H_

#include <functional>

#include "VisualElement.h"

/**
 * @brief base class for interactive UI elements
*/
class UIElement : public VisualElement {
    public:
        UIElement(Adafruit_GFX& display);
        virtual ~UIElement() { }
        
        /**
         * @brief sets background to _focusColour
        */
        virtual void focus();

        /**
         * @brief reverts background colour to default
        */
        virtual void unfocus();

        /**
         * @brief pure virtual function so derived classes can define custom select animation
        */
        virtual void select() = 0;

        UIElement& setFocusColour(uint16_t colour);

    protected:
        uint16_t _focusColour = 0;

};

#endif
