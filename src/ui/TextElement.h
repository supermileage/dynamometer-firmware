#ifndef _TEXT_ELEMENT_H_
#define _TEXT_ELEMENT_H_

#include "RectangularElement.h"
#include "TextComponent.h"

class TextElement : public RectangularElement {
    public:
        TextElement(Adafruit_GFX& display);
        ~TextElement();
        
        /**
         * @brief draw text element to screen
        */
        void draw() override;

        /**
         * @brief redraw text to screen
         * @note doesn't draw background or border to screen
        */
        void redraw();

        /**
         * @brief returns text component owned by this text element
        */
        TextComponent& getTextComponent();

    private:
        TextComponent _textComponent;

};

#endif
