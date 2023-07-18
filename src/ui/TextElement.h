#ifndef _TEXT_ELEMENT_H_
#define _TEXT_ELEMENT_H_

#include <memory>

#include "RectangularElement.h"
#include "ValueTextComponent.h"

class TextElement : public RectangularElement {
    public:
        TextElement(TFT_eSPI& display, bool numeric = false);
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
         * @warning unsafe to save TextComponent as reference
        */
        TextComponent& getTextComponent();

        /**
         * @brief computes own dimensions based on string and font
        */
        TextElement& computeDimensions();

    private:
        std::shared_ptr<TextComponent> _textComponent = nullptr;
};

#endif
