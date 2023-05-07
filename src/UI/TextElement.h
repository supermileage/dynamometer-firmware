#ifndef _TEXT_ELEMENT_H_
#define _TEXT_ELEMENT_H_

#include "VisualElement.h"
#include "TextComponent.h"

class TextElement : public VisualElement {
    public:
        TextElement(Adafruit_ILI9341& display);
        ~TextElement();
        
        /**
         * @brief draw text element to screen
        */
        void draw() override;

        /**
         * @brief clear text element from screen
        */
        void clear() override;

        /**
         * @brief returns text component owned by this text element
        */
        TextComponent& getTextComponent();

    private:
        TextComponent _textComponent;

        void _onResize() override;

};

#endif
