#ifndef _UI_ELEMENT_H_
#define _UI_ELEMENT_H_

#include <functional>

#include "RectangularElement.h"

/**
 * @brief base class for interactive UI elements
*/
class UIElement : public RectangularElement {
    public:
        UIElement(TFT_eSPI& display);
        virtual ~UIElement() { }
        
        /**
         * @brief sets background to _focusColour
        */
        virtual void focus();

        /**
         * @brief reverts background colour to default
        */
        virtual void revert();

        /**
         * @brief sets background to _selectColour
        */
        virtual void select();

        UIElement& setFocusColour(uint16_t colour);
        UIElement& setSelectColour(uint16_t colour);

    protected:
        uint16_t _focusColour = 0;
        uint16_t _selectColour = 0;

};

#endif
