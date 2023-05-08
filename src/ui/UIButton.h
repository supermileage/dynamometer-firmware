#ifndef _UI_BUTTON_H_
#define _UI_BUTTON_H_

#include "Adafruit_GFX.h"
#include "UIElement.h"
#include "TextComponent.h"

class UIButton : public UIElement {
    public:
        UIButton(Adafruit_GFX& display);
        ~UIButton();
        
        /**
         * @brief draw button to screen
        */
        void draw() override;

        /**
         * @brief execute button focus effect
        */
        void focus() override;

        /**
         * @brief execute button unfocus effect
        */
        void unfocus() override;

        /**
         * @brief execute button selection effect
        */
        void select() override;

        /**
         * @brief set focussable font colour of this button
        */
        UIButton& setFontFocusColour(uint16_t colour);

        /**
         * @brief get text component owned by this button
        */
        TextComponent& getTextComponent();

    private:
        TextComponent _textComponent;
        uint16_t _fontFocusColour = 0;

        void _onResize() override;
};

#endif