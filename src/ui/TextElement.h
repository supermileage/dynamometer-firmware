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
         * @brief returns text component owned by this text element
        */
        TextComponent& getTextComponent();

    private:
        TextComponent _textComponent;

};

#endif
