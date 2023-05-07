#ifndef _UI_BUTTON_H_
#define _UI_BUTTON_H_

#include "Adafruit_ILI9341.h"
#include "UIElement.h"
#include "TextComponent.h"

class UIButton : public UIElement {
    public:
        UIButton(Adafruit_ILI9341& display);
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
         * @brief get text component owned by this button
        */
        TextComponent& getTextComponent();

    private:
        TextComponent _textComponent;

        void _onResize() override;
};

#endif