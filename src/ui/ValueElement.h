#ifndef _VALUE_ELEMENT_H_
#define _VALUE_ELEMENT_H_

#include "Container.h"
#include "TextElement.h"

class ValueElement : public Container {
    public:
        ValueElement(Adafruit_GFX& display) : Container(display) {
            _labelElement = std::make_shared<TextElement>(_display);
            _valueElement = std::make_shared<TextElement>(_display);
            _unitsElement = std::make_shared<TextElement>(_display);

            Container::addVisualElement(_labelElement, Container::BottomRight);
            Container::addVisualElement(_valueElement, Container::CentreMiddle);
            Container::addVisualElement(_unitsElement, Container::TopLeft);

            setPadding(2);
        }

        ValueElement& configureLabel(String& label, GFXfont const* font, uint16_t colour,
            uint8_t w = 1, uint8_t h = 1) {
                _configureText(_labelElement, label, font, colour, w, h);
                return *this;
        }

        ValueElement& configureValue(String& value, GFXfont const* font, uint16_t colour,
            uint8_t w = 1, uint8_t h = 1) {
                _configureText(_valueElement, value, font, colour, w, h);
                return *this;
        }

        ValueElement& configureUnits(String& units, GFXfont const* font, uint16_t colour,
            uint8_t w = 1, uint8_t h = 1) {
                _configureText(_unitsElement, units, font, colour, w, h);
                return *this;
        }

        void setValue(String& value) {
            _valueElement->getTextComponent()
                .setDisplayString(value);
        }

        void updateValue(String& value) {
            setValue(value);
            _valueElement->redraw();
        }

        void redraw() {
            _valueElement->redraw();
        }

    private:
        std::shared_ptr<TextElement> _labelElement = nullptr;
        std::shared_ptr<TextElement> _valueElement = nullptr;
        std::shared_ptr<TextElement> _unitsElement = nullptr;


        void _configureText(std::shared_ptr<TextElement> element, String& text, GFXfont const* font,
            uint16_t colour, uint8_t w, uint8_t h) {
                element->getTextComponent()
                    .setDisplayString(text)
                    .setFont(font)
                    .setFontColour(colour)
                    .setFontSize(w, h);
                element->computeDimensions();
        }
};

#endif