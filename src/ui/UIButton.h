#ifndef _UI_BUTTON_H_
#define _UI_BUTTON_H_

#include "TFT_eSPI.h"
#include "UIElement.h"
#include "TextComponent.h"

class UIButton : public UIElement {
    public:
        UIButton(TFT_eSPI& display);
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
         * @brief revert styling to default (undoes focus/select)
        */
        void revert() override;

        /**
         * @brief execute button selection effect
        */
        void select() override;

        /**
         * @brief set focussable font colour of this button
        */
        UIButton& setFontFocusColour(uint16_t colour);

        /**
         * @brief set focussable font colour of this button
        */
        UIButton& setFontSelectColour(uint16_t colour);

        /**
         * @brief get text component owned by this button
        */
        TextComponent& getTextComponent();

    private:
        TextComponent _textComponent;
        uint16_t _fontFocusColour = 0;
        uint16_t _fontSelectColour = 0;

        void _recolourText(uint16_t colour);
};

#endif