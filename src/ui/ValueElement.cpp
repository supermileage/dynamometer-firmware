#include "ValueElement.h"


ValueElement::ValueElement(TFT_eSPI& display) : Container(display) {
    _labelElement = std::make_shared<TextElement>(_display);
    _valueElement = std::make_shared<TextElement>(_display, true);
    _unitsElement = std::make_shared<TextElement>(_display);

    Container::addVisualElement(_labelElement, Container::TopRight);
    Container::addVisualElement(_valueElement, Container::CentreMiddle);
    Container::addVisualElement(_unitsElement, Container::BottomLeft);
}

ValueElement& ValueElement::configureLabel(String& label, GFXfont const* font, uint16_t colour, uint8_t w, uint8_t h) {
        _configureText(_labelElement, label, font, colour, w, h);
        return *this;
}

ValueElement& ValueElement::configureValue(String& value, GFXfont const* font, uint16_t colour, uint8_t w, uint8_t h) {
        _configureText(_valueElement, value, font, colour, w, h);
        return *this;
}

ValueElement& ValueElement::configureUnits(String& units, GFXfont const* font, uint16_t colour, uint8_t w, uint8_t h) {
        _configureText(_unitsElement, units, font, colour, w, h);
        return *this;
}

void ValueElement::align() {
    _labelElement->computeDimensions();
    _valueElement->computeDimensions();
    _unitsElement->computeDimensions();

    if (_orientation == Container::Row) {
        _width += _labelElement->getWidth();
        _width += _valueElement->getWidth();
        _width += _unitsElement->getWidth();
        _width += (_padding * 4);
        _height = (_padding * 2) +
            max(max(_labelElement->getHeight(), _valueElement->getHeight()), _unitsElement->getHeight());
    } else {
        _height += _labelElement->getHeight();
        _height += _valueElement->getHeight();
        _height += _unitsElement->getHeight();
        _height += (_padding * 4);
        _width = (_padding * 2) +
            max(max(_labelElement->getWidth(), _valueElement->getWidth()), _unitsElement->getWidth());
    }
    Container::align();
}

void ValueElement::setValue(String& value) {
    _valueElement->getTextComponent()
        .setDisplayString(value);
}

void ValueElement::updateValue(String& value) {
    setValue(value);
    _valueElement->redraw();
}

void ValueElement::redraw() {
    _valueElement->redraw();
}

void ValueElement::_configureText(std::shared_ptr<TextElement> element, String& text, GFXfont const* font,
    uint16_t colour, uint8_t w, uint8_t h) {
        element->getTextComponent()
            .setDisplayString(text)
            .setFont(font)
            .setFontColour(colour)
            .setFontSize(w, h);
}