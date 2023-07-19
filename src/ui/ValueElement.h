#ifndef _VALUE_ELEMENT_H_
#define _VALUE_ELEMENT_H_

#include "Arduino.h"

#include "Container.h"
#include "TextElement.h"

/**
 * @brief ValueElement class represents a display value with label, value and units
*/
class ValueElement : public Container {
    public:
        ValueElement(TFT_eSPI& display);

        /**
         * @brief configures text for label
        */
        ValueElement& configureLabel(String& label, GFXfont const* font, uint16_t colour,
            uint8_t w = 1, uint8_t h = 1);

        /**
         * @brief configures text for value
         * @note this initial value string should be formatted to match how you would like the value to
         *       be displayed -- ie. if you want a decimal from 0 to 99.99, enter 00.00 as initial string
        */
        ValueElement& configureValue(String& value, GFXfont const* font, uint16_t colour,
            uint8_t w = 1, uint8_t h = 1);

        /**
         * @brief configures units for this value element
        */
        ValueElement& configureUnits(String& units, GFXfont const* font, uint16_t colour,
            uint8_t w = 1, uint8_t h = 1);

        /**
         * @brief computes size of value element based on label, value and units
         * @note user must configure all desired display elements (label, value, units) before calling this
        */
        void align() override;

        /**
         * @brief sets new value without updating display
        */
        void setValue(String& value);

        /**
         * @brief sets value and updates display
        */
        void updateValue(String& value);

        /**
         * @brief draws new value to screen
         * @note the difference between ValueElement::draw and ValueElement::redraw is that
         *       draw will erase and re-render the entire string, whereas redraw performs
         *       an optimized draw
        */
        void redraw();

    private:
        std::shared_ptr<TextElement> _labelElement = nullptr;
        std::shared_ptr<TextElement> _valueElement = nullptr;
        std::shared_ptr<TextElement> _unitsElement = nullptr;

        /**
         * @brief internal method for configuring text elements
        */
        void _configureText(std::shared_ptr<TextElement> element, String& text, GFXfont const* font,
            uint16_t colour, uint8_t w, uint8_t h);
};

#endif